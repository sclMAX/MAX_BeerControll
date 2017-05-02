#ifndef OLLA_H
    #define OLLA_H

    #include <stdint.h>
    #include <avr/io.h>
    #include <avr/interrupt.h>
    #include <avr/pgmspace.h>
    #include "Arduino.h"

    class Olla{
        public:
            Olla (uint8_t pinQ, uint8_t pinS);

            static float current_temperature;
            static int current_temperature_raw;
            static volatile bool isQuemadorOn;
        private:
            const uint8_t pinQuemador;
            const uint8_t pinSensor;

    };

#endif //OLLA_H