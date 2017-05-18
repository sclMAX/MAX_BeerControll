#ifndef BOMBA_H
#define BOMBA_H

#include "Arduino.h"

class Bomba
{
  public:
    volatile bool isOn = false;
    int timePurgaOn = 1;
    int timePurgaOff = 2;
    unsigned int purgas = 4;
    unsigned int purgaCount = 0;

  private:
    const int pin;

  public:
    Bomba(int PIN);
    void on();
    void off();
};
#endif //BOMBA_H