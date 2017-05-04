#ifndef OLLA_H
    #define OLLA_H

    #include <stdint.h>
    #include <avr/io.h>
    #include <avr/interrupt.h>
    #include <avr/pgmspace.h>
    #include "Arduino.h"

    class Olla{
        public:
            Olla (String);
            void setTemp(float);
            void setTempTarget(float);
            void setHisteresis(int, int);
            void calentar();
            void apagar();
            float getTemp();
            volatile bool isQuemadorOn = false;
        private:
            int histeresisInf = 0;
            int histeresisSup = 0;
            String nombre;
            float tempTarget = 0.00;
            volatile float temp = 0;
            volatile bool isCalentar = false;
    };

#endif //OLLA_H