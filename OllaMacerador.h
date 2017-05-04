#ifndef OLLAMACERADOR_H
#define OLLAMACERADOR_H

#include "Olla.h"
#include "config.h"
#include "fastio.h"
#include "macros.h"

class OllaMacerador : public Olla {
public:
  OllaMacerador(String _nombre) : Olla(_nombre){SET_INPUT(QUEMADOR_MACERADOR_PIN);};
  void setTemp(float _temp) {
    if (temp != _temp) {
      temp = _temp;
      if (isCalentar) {
        if ((temp) <= (tempTarget - histeresisInf)) {
          WRITE(QUEMADOR_MACERADOR_PIN, HIGH);
          isQuemadorOn = true;
        } else if (((temp) >= (tempTarget + histeresisSup))) {
          WRITE(QUEMADOR_MACERADOR_PIN, LOW);
          isQuemadorOn = false;
        }
      } else {
        WRITE(QUEMADOR_MACERADOR_PIN, LOW);
        isQuemadorOn = false;
      }
    }
  };
};

#endif // OLLAMACERADOR_H