
#ifndef TEMPERATURE_H
  #define TEMPERATURE_H

  #include "thermistortables.h"
  #include "config.h"
  #include "MarlinConfig.h"

  class Temperature {

    public:

      static float currentTempLicor,
                   currentTempMacerador,
                   currentTempHervido;
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

      Temperature();

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
      static void updateTemp();

      static float getTempLicor() { return currentTempLicor;}
      static float getTempMacerador(){ return currentTempMacerador;}
      static float getTempHervido(){return currentTempHervido;}

    private:

      static void set_current_temp_raw();
      static void updateTemperaturesFromRawValues();
  };
  extern Temperature thermalManager;
#endif // TEMPERATURE_H
