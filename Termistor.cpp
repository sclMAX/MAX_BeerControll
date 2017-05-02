#ifndef TERMISTOR_CPP
#define TERMISTOR_CPP

#include "Termistor.h"
#define SET_ADMUX_ADCSRA(pin)          \
    ADMUX = _BV(REFS0) | (pin & 0x07); \
    SBI(ADCSRA, ADSC)
#define PGM_RD_W(x) (short)pgm_read_word(&x)
#define OVERSAMPLENR 16
const short temptable_1[][2] PROGMEM = {
    {23 * OVERSAMPLENR, 300},
    {25 * OVERSAMPLENR, 295},
    {27 * OVERSAMPLENR, 290},
    {28 * OVERSAMPLENR, 285},
    {31 * OVERSAMPLENR, 280},
    {33 * OVERSAMPLENR, 275},
    {35 * OVERSAMPLENR, 270},
    {38 * OVERSAMPLENR, 265},
    {41 * OVERSAMPLENR, 260},
    {44 * OVERSAMPLENR, 255},
    {48 * OVERSAMPLENR, 250},
    {52 * OVERSAMPLENR, 245},
    {56 * OVERSAMPLENR, 240},
    {61 * OVERSAMPLENR, 235},
    {66 * OVERSAMPLENR, 230},
    {71 * OVERSAMPLENR, 225},
    {78 * OVERSAMPLENR, 220},
    {84 * OVERSAMPLENR, 215},
    {92 * OVERSAMPLENR, 210},
    {100 * OVERSAMPLENR, 205},
    {109 * OVERSAMPLENR, 200},
    {120 * OVERSAMPLENR, 195},
    {131 * OVERSAMPLENR, 190},
    {143 * OVERSAMPLENR, 185},
    {156 * OVERSAMPLENR, 180},
    {171 * OVERSAMPLENR, 175},
    {187 * OVERSAMPLENR, 170},
    {205 * OVERSAMPLENR, 165},
    {224 * OVERSAMPLENR, 160},
    {245 * OVERSAMPLENR, 155},
    {268 * OVERSAMPLENR, 150},
    {293 * OVERSAMPLENR, 145},
    {320 * OVERSAMPLENR, 140},
    {348 * OVERSAMPLENR, 135},
    {379 * OVERSAMPLENR, 130},
    {411 * OVERSAMPLENR, 125},
    {445 * OVERSAMPLENR, 120},
    {480 * OVERSAMPLENR, 115},
    {516 * OVERSAMPLENR, 110},
    {553 * OVERSAMPLENR, 105},
    {591 * OVERSAMPLENR, 100},
    {628 * OVERSAMPLENR, 95},
    {665 * OVERSAMPLENR, 90},
    {702 * OVERSAMPLENR, 85},
    {737 * OVERSAMPLENR, 80},
    {770 * OVERSAMPLENR, 75},
    {801 * OVERSAMPLENR, 70},
    {830 * OVERSAMPLENR, 65},
    {857 * OVERSAMPLENR, 60},
    {881 * OVERSAMPLENR, 55},
    {903 * OVERSAMPLENR, 50},
    {922 * OVERSAMPLENR, 45},
    {939 * OVERSAMPLENR, 40},
    {954 * OVERSAMPLENR, 35},
    {966 * OVERSAMPLENR, 30},
    {977 * OVERSAMPLENR, 25},
    {985 * OVERSAMPLENR, 20},
    {993 * OVERSAMPLENR, 15},
    {999 * OVERSAMPLENR, 10},
    {1004 * OVERSAMPLENR, 5},
    {1008 * OVERSAMPLENR, 0} // safety
};
#define TEMPTABLE temptable_1
#define TEMPTABLE_LEN COUNT(TEMPTABLE)

#define ANALOG_SELECT(pin) \
    do                     \
    {                      \
        SBI(DIDR0, pin);   \
    } while (0)
// Set analog inputs
ADCSRA = _BV(ADEN) | _BV(ADSC) | _BV(ADIF) | 0x07;
DIDR0 = 0;
static unsigned char temp_count = 0;

Termistor::Termistor(uint8_t pinS)
{
    this->pinSensor = pinS;
    ANALOG_SELECT(pinS);
}
//public:

float Termistor::getTemp()
{
    return this->current_temperature;
}

void Termistor::update()
{
    START_ADC(this->pinSensor);
    raw_temp_value += ADC;
    temp_count++;
    if (temp_count >= OVERSAMPLENR)
    { // 10 * 16 * 1/(16000000/64/256)  = 164ms.
        // Update the raw values if they've been read. Else we could be updating them during reading.
        if (!temp_meas_ready)
        {
            current_temperature_raw = raw_temp_value;
            temp_meas_ready = true;
        }
        temp_count = 0;
        raw_temp_value = 0;
    }
}

//pribate:
float Termistor::analog2temp(int raw)
{
    float celsius = 0;
    byte i;
    for (i = 1; i < TEMPTABLE_LEN; i++)
    {
        if (PGM_RD_W(TEMPTABLE[i][0]) > raw)
        {
            celsius = PGM_RD_W(TEMPTABLE[i - 1][1]) +
                      (raw - PGM_RD_W(TEMPTABLE[i - 1][0])) *
                          (float)(PGM_RD_W(TEMPTABLE[i][1]) - PGM_RD_W(TEMPTABLE[i - 1][1])) /
                          (float)(PGM_RD_W(TEMPTABLE[i][0]) - PGM_RD_W(TEMPTABLE[i - 1][0]));
            break;
        }
    }

    // Overflow: Set to last value in the table
    if (i == TEMPTABLE_LEN)
    {
        celsius = PGM_RD_W(TEMPTABLE[i - 1][1]);
    }
    return celsius;
}

#endif //TERMISTOR_CPP