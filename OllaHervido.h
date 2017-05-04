#ifndef OLLA_HERVIDO_H
#define OLLA_HERVIDO_H

#include "Olla.h"
#include "config.h"
#include "fastio.h"
#include "macros.h"

class OllaHervido : public Olla {
public:
  OllaHervido(String _nombre) : Olla(_nombre){SET_INPUT(QUEMADOR_HERVIDO_PIN);};
  void setTemp(float _temp) {
    if (temp != _temp) {
      temp = _temp;
      if (isCalentar) {
        if ((temp) <= (tempTarget - histeresisInf)) {
          WRITE(QUEMADOR_HERVIDO_PIN, HIGH);
          isQuemadorOn = true;
        } else if (((temp) >= (tempTarget + histeresisSup))) {
          WRITE(QUEMADOR_HERVIDO_PIN, LOW);
          isQuemadorOn = false;
        }
      } else {
        WRITE(QUEMADOR_HERVIDO_PIN, LOW);
        isQuemadorOn = false;
      }
    }
  };
};

#endif // OLLA_HERVIDO_H