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
        protected:
            volatile float temp = 0;
            volatile bool isCalentar = false;
            float tempTarget = 0.00;            
            int histeresisInf = 0;
            int histeresisSup = 0;
        private:
            String nombre;
            
    };
    Olla::Olla(String _nombre){
        Olla::nombre = _nombre;
    }

    void Olla::setTempTarget(float _tempTarget){
        Olla::tempTarget = _tempTarget;
    }

    void Olla::setTemp(float _temp){
        if(temp != _temp){
            temp = _temp;
        };
    }

    void Olla::setHisteresis(int _hiesteresisSup, int _histeresisInf){
        histeresisInf = _histeresisInf;
        histeresisSup = _hiesteresisSup;
    }

    void Olla::calentar(){
        isCalentar = true;
    }

    void Olla::apagar(){
        isCalentar = false;
    }

    float Olla::getTemp(){
        return temp;
    }

#endif //OLLA_H