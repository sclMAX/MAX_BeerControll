
#ifndef TEMPERATURE_H
  #define TEMPERATURE_H

  #include <inttypes.h>
  #include <math.h>
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <avr/eeprom.h>
  #include <avr/interrupt.h>
  #include <avr/pgmspace.h>
  #include <util/delay.h>
  #include "thermistortables.h"
  #include "config.h"
  #include "Olla.h"
  #include "Arduino.h"

  class Temperature {

    public:

      static Olla *pLicor, *pMacerador, *pHervido;
      static int   currentTempLicorRaw,
                   currentTempMaceradorRaw,
                   currentTempHervidoRaw;

    private:
      static volatile bool temp_meas_ready;
      static unsigned long rawTempLicorValue, rawTempMaceradorValue, rawTempHervidoValue;

    public:

      /**
      * Instance Methods
      */

      Temperature(Olla&, Olla&, Olla&);

      void init();

      /**
      * Static (class) methods
      */
      static float analog2temp(int raw);

      /**
      * Called from the Temperature ISR
      */
      static void isr();

      /**
      * Call periodically to manage heaters
      */
      static void manageTemp();
    private:

      static void set_current_temp_raw();
      static void updateTemperaturesFromRawValues();
  };
#endif // TEMPERATURE_H
