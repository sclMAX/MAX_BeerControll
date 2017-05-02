#ifndef TERMISTOR_H
#define TERMISTOR_H

#include "macros.h"
#include "Termistor.cpp"
class Termistor
{
  public:
    Termistor(uint8_t);
    static float getTemp();
    static void update();

    static unsigned long raw_temp_value;

  private:
    const uint8_t pinSensor;
    static volatile bool temp_meas_ready;
    static float current_temp;
    static int current_temp_raw;
    static float analog2temp(int);
};
#endif //TERMISTOR_H