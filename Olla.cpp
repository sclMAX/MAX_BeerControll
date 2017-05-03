#ifndef OLLA_CPP
#define OLLA_CPP

    #include "Olla.h".
    #include "fastio.h"
    #include "macros.h"

    #define QUEMADOR_ON WRITE(STRINGIFY(pinQuemador), HIGH); isQuemadorOn = true;
    #define QUEMADOR_OFF WRITE(STRINGIFY(pinQuemador), LOW); isQuemadorOn = false;

    Olla::Olla(int _pinQuemador, int _pinSensor, String _nombre){
        pinQuemador = _pinQuemador;
        pinSensor = _pinSensor;
        nombre = _nombre;
        SET_OUTPUT(STRINGIFY(pinQuemador));
    }

    void Olla::setTempTarget(float _tempTarget){
        tempTarget = _tempTarget;
    }

    void Olla::setTemp(float _temp){
        if(temp != _temp){
            temp = _temp;
            if(isCalentar){ 
                if((temp) <= (tempTarget - histeresisInf)){
                    QUEMADOR_ON;
                }else if(((temp) >= (tempTarget + histeresisSup))){
                    QUEMADOR_OFF;
                }
            }else{
                QUEMADOR_OFF;
            }
        }
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

    int Olla::getPinQuemador(){return pinQuemador;}
    int Olla::getPinSensor(){return pinSensor;}
#endif //OLLA_CPP