#ifndef OLLALICOR_H
#define OLLALICOR_H

#include "Olla.h"
#include "config.h"
#include "fastio.h"
#include "macros.h"

class OllaLicor : public Olla {
public:
  OllaLicor(String _nombre) : Olla(_nombre){SET_INPUT(QUEMADOR_LICOR_PIN)};
  void setTemp(float _temp) {
    if (temp != _temp) {
      temp = _temp;
      if (isCalentar) {
        if ((temp) <= (tempTarget - histeresisInf)) {
          WRITE(QUEMADOR_LICOR_PIN, HIGH);
          isQuemadorOn = true;
        } else if (((temp) >= (tempTarget + histeresisSup))) {
          WRITE(QUEMADOR_LICOR_PIN, LOW);
          isQuemadorOn = false;
        }
      } else {
        WRITE(QUEMADOR_LICOR_PIN, LOW);
        isQuemadorOn = false;
      }
    }
  };
};

#endif // OLLALICOR_H