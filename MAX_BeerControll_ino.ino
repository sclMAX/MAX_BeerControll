/*
* Beer Control v1.0 by MAX
* 2017-05-07 inicio desarrollo
* controlador para proceso de coccion de cerveza artesanal
*/

#include "config.h"
#include "encoderControl.h"
#include "temperature.h"
#include <TimerOne.h>

void setup() {

  Serial.begin(9600);
  encoder = new ClickEncoder(EN1, EN2, ENC, ENSTP);
  Timer1.initialize(1000);
  Timer1.attachInterrupt(timerIsr);
  last = -1;
  tempManager.init();
  initMenus(menu);
  tempManager.Licor.etiqueta = 'L';
  tempManager.Macerador.etiqueta = 'M';
  tempManager.Hervido.etiqueta = 'H';
}

void loop() {
  tempManager.manageTemp();
  manageEncoder();
  updateLCD();
}
