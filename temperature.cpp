/**
 * temperature.cpp - temperature control
 */

#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "temperature.h"
#include "thermistortables.h"
#include <avr/eeprom.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

enum TempState {
  PrepareTempLicor,
  MeasureTempLicor,
  PrepareTempMacerador,
  MeasureTempMacerador,
  PrepareTempHervido,
  MeasureTempHervido,
  StartupDelay // Startup, delay initial temp reading a tiny bit so the hardware
               // can settle
};

Temperature thermalManager;

// public:

float Temperature::currentTempLicor = 0.0,
      Temperature::currentTempMacerador = 0.0,
      Temperature::currentTempHervido = 0.0;
int Temperature::currentTempLicorRaw = 0,
    Temperature::currentTempMaceradorRaw = 0,
    Temperature::currentTempHervidoRaw = 0;

volatile bool Temperature::temp_meas_ready = false;
unsigned long Temperature::rawTempLicorValue = 0;
unsigned long Temperature::rawTempMaceradorValue = 0;
unsigned long Temperature::rawTempHervidoValue = 0;

/**
 * Class and Instance Methods
 */

Temperature::Temperature() {}

/**
 * Actualiza valores de temperatura
 */
void Temperature::updateTemp() {

  if (!temp_meas_ready)
    return;
  updateTemperaturesFromRawValues();
} // manage_heateu

#define PGM_RD_W(x) (short)pgm_read_word(&x)

// Derived from RepRap FiveD extruder::getTemperature()
// For bed temperature measurement.
float Temperature::analog2temp(int raw) {
  float celsius = 0;
  byte i;

  for (i = 1; i < TEMPTABLE_LEN; i++) {
    if (PGM_RD_W(TEMPTABLE[i][0]) > raw) {
      celsius = PGM_RD_W(TEMPTABLE[i - 1][1]) +
                (raw - PGM_RD_W(TEMPTABLE[i - 1][0])) *
                    (float)(PGM_RD_W(TEMPTABLE[i][1]) -
                            PGM_RD_W(TEMPTABLE[i - 1][1])) /
                    (float)(PGM_RD_W(TEMPTABLE[i][0]) -
                            PGM_RD_W(TEMPTABLE[i - 1][0]));
      break;
    }
  }

  // Overflow: Set to last value in the table
  if (i == TEMPTABLE_LEN)
    celsius = PGM_RD_W(TEMPTABLE[i - 1][1]);
  return celsius;
}

/**
 * Get the raw values into the actual temperatures.
 * The raw values are created in interrupt context,
 * and this function is called from normal context
 * as it would block the stepper routine.
 */
void Temperature::updateTemperaturesFromRawValues() {
  currentTempLicor = Temperature::analog2temp(currentTempLicorRaw);
  currentTempMacerador = Temperature::analog2temp(currentTempMaceradorRaw);
  currentTempHervido = Temperature::analog2temp(currentTempHervidoRaw);
  CRITICAL_SECTION_START;
  temp_meas_ready = false;
  CRITICAL_SECTION_END;
}

/**
 * Initialize the temperature manager
 * The manager is implemented by periodic calls to manage_heater()
 */
void Temperature::init() {

#ifdef DIDR2
#define ANALOG_SELECT(pin)                                                     \
  do {                                                                         \
    if (pin < 8)                                                               \
      SBI(DIDR0, pin);                                                         \
    else                                                                       \
      SBI(DIDR2, pin - 8);                                                     \
  } while (0)
#else
#define ANALOG_SELECT(pin)                                                     \
  do {                                                                         \
    SBI(DIDR0, pin);                                                           \
  } while (0)
#endif

  // Set analog inputs
  ADCSRA = _BV(ADEN) | _BV(ADSC) | _BV(ADIF) | 0x07;
  DIDR0 = 0;
#ifdef DIDR2
  DIDR2 = 0;
#endif
  ANALOG_SELECT(TEMP_LICOR_PIN);
  ANALOG_SELECT(TEMP_MACERADOR_PIN);
  ANALOG_SELECT(TEMP_HERVIDO_PIN);
  // Use timer0 for temperature measurement
  // Interleave temperature interrupt with millies interrupt
  OCR0B = 128;
  SBI(TIMSK0, OCIE0B);

  // Wait for temperature measurement to settle
  delay(250);
}
/**
 * Get raw temperatures
 */
void Temperature::set_current_temp_raw() {
  currentTempLicorRaw = rawTempLicorValue;
  currentTempMacerador = rawTempMaceradorValue;
  currentTempHervidoRaw = rawTempHervidoValue;
  temp_meas_ready = true;
}

/**
 * Timer 0 is shared with millies
 *  - Update the raw temperature values
 */
ISR(TIMER0_COMPB_vect) { Temperature::isr(); }

void Temperature::isr() {

  static unsigned char temp_count = 0;
  static TempState temp_state = StartupDelay;
#define SET_ADMUX_ADCSRA(pin)                                                  \
  ADMUX = _BV(REFS0) | (pin & 0x07);                                           \
  SBI(ADCSRA, ADSC)
#ifdef MUX5
#define START_ADC(pin)                                                         \
  if (pin > 7)                                                                 \
    ADCSRB = _BV(MUX5);                                                        \
  else                                                                         \
    ADCSRB = 0;                                                                \
  SET_ADMUX_ADCSRA(pin)
#else
#define START_ADC(pin)                                                         \
  ADCSRB = 0;                                                                  \
  SET_ADMUX_ADCSRA(pin)
#endif

  // Prepare or measure a sensor, each one every 12th frame
  switch (temp_state) {
  case PrepareTempLicor:
    START_ADC(TEMP_LICOR_PIN);
    temp_state = MeasureTempLicor;
    break;
  case MeasureTempLicor:
    rawTempLicorValue += ADC;
    temp_state = PrepareTempMacerador;
    break;

  case PrepareTempMacerador:
    START_ADC(TEMP_MACERADOR_PIN);
    temp_state = MeasureTempMacerador;
    break;
  case MeasureTempMacerador:
    rawTempMaceradorValue += ADC;
    temp_state = PrepareTempHervido;
    break;

  case PrepareTempHervido:
    START_ADC(TEMP_HERVIDO_PIN);
    temp_state = MeasureTempHervido;
    break;
  case MeasureTempHervido:
    rawTempHervidoValue += ADC;
    temp_state = PrepareTempLicor;
    temp_count++;
    break;
  case StartupDelay:
    temp_state = PrepareTempLicor;
    break;
  }

  if (temp_count >= OVERSAMPLENR) { // 10 * 16 * 1/(16000000/64/256)  = 164ms.
    // Update the raw values if they've been read. Else we could be updating
    // them during reading.
    if (!temp_meas_ready)
      set_current_temp_raw();
    temp_count = 0;
    rawTempLicorValue = 0;
    rawTempMaceradorValue = 0;
    rawTempHervidoValue = 0;
  } // temp_count >= OVERSAMPLENR
}