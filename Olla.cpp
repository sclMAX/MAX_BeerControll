#ifndef OLLA_CPP
#define OLLA_CPP

    #include "Olla.h"

    Olla::Olla(String _nombre){
        nombre = _nombre;
    }

    void Olla::setTempTarget(float _tempTarget){
        tempTarget = _tempTarget;
    }

    void Olla::setTemp(float _temp){
        
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
#endif //OLLA_CPP