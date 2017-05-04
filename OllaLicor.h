#ifndef OLLALICOR_H
#define OLLALICOR_H

#include "fastio.h"
#include "macros.h"
#include <stdio.h>
#include <stdlib.h>
#include "Arduino.h"

class OllaLicor {
    public:
        OllaLicor(char);
        void prender();
        void apagar();
        void setTempTarget (float); //Temperatura Objetivo
        void setTemperatura (float); //Temperatura actual
        void setHisteresis (float, float); //Margen inferior y superior para Histeresis
        float getTemperatura(); 
        char getEtiqueta();
        volatile bool isCalentando = false;
        volatile bool isQuemadorOn = false;
    private:
        char _etiqueta;
        float _tempTarget = 0.00;
        volatile float _temperatura = 0.00;
        float _histeresisInf = 1.00;
        float _histeresisSup = 0.00;
};

OllaLicor::OllaLicor(char etiqueta){
    _etiqueta = etiqueta;
    SET_INPUT(QUEMADOR_LICOR_PIN);
    WRITE(QUEMADOR_LICOR_PIN, LOW);
}

void OllaLicor::prender(){
    isCalentando = true;
}

void OllaLicor::apagar(){
    isCalentando = false;
}
void OllaLicor::setTempTarget(float tempTarget){
    _tempTarget = tempTarget;
}

void OllaLicor::setTemperatura(float temperatura){
    if(_temperatura != temperatura){
        _temperatura = temperatura;
        if(isCalentando){
            if((_temperatura <= (_tempTarget - _histeresisInf)) && (!isQuemadorOn)){
                 WRITE(QUEMADOR_LICOR_PIN, HIGH);
                 isQuemadorOn = true;
            }else if((_temperatura >= (_tempTarget + _histeresisSup))&&(isQuemadorOn)){
                WRITE(QUEMADOR_LICOR_PIN, LOW);
                isQuemadorOn = false;
            }
        }
    }
}

void OllaLicor::setHisteresis(float histeresisSup, float histeresisInf){
    _histeresisSup = histeresisSup;
    _histeresisInf = histeresisInf;
}

float OllaLicor::getTemperatura(){
    return _temperatura;
}

char OllaLicor::getEtiqueta(){
    return _etiqueta;
}

#endif //OLLALICOR_H