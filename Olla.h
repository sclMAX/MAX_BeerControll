#ifndef OLLA_H
    #define OLLA_H

    #include <stdint.h>
    #include <avr/io.h>
    #include <avr/interrupt.h>
    #include <avr/pgmspace.h>
    #include "Arduino.h"

    class Olla{
        public:
            Olla (int, int, String);
            void setTemp(float);
            void setTempTarget(float);
            void setHisteresis(int, int);
            void calentar();
            void apagar();
            float getTemp();
            int getPinQuemador();
            int getPinSensor();
            volatile bool isQuemadorOn = false;
        private:
            int pinQuemador;
            int pinSensor;
            int histeresisInf = 0;
            int histeresisSup = 0;
            String nombre;
            float tempTarget = 0.00;
            volatile float temp = 0;
            volatile bool isCalentar = false;
    };

#endif //OLLA_H