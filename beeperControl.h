#ifndef BEEPERCONTROL_H
#define BEEPERCONTROL_H

#include "fastio.h"
#include "config.h"

class Beeper {

private:
  static unsigned long inicioBeep;
  static unsigned long inicioEspera;
  static int cantidadBeeps;
  static unsigned long _duracion;
  static unsigned long _espacio;

public:
  Beeper() {
    SET_OUTPUT(BEEPER_PIN);
    inicioBeep = 0;
    inicioEspera = 0;
    cantidadBeeps = 0;
    _duracion = 0;
    _espacio = 0;
  };
  void update(unsigned long now) {
    if (cantidadBeeps > 0) {
      if ((inicioBeep == 0)) {
        if (inicioEspera == 0) {
          inicioBeep = now;
          on();
        } else if (now >= (inicioEspera + _espacio)) {
          inicioEspera = 0;
        }
      } else if (now >= (inicioBeep + _duracion)) {
        inicioBeep = 0;
        off();
        cantidadBeeps--;
        inicioEspera = (cantidadBeeps > 0) ? now : 0;
      }
    }
  };
  void on() { WRITE(BEEPER_PIN, HIGH); };
  void off() { WRITE(BEEPER_PIN, LOW); };
  void beep(unsigned long duracion) {
    cantidadBeeps = 1;
    _duracion = duracion;
  };
  void beeps(int cantidad, unsigned long duracion, unsigned long espacio) {
    cantidadBeeps = cantidad;
    _duracion = duracion;
    _espacio = espacio;
  };
};

extern Beeper beeper;
#endif // BEEPERCONTROL_H