/*
* Beer Control v1.0 by MAX
* 2017-05-07 inicio desarrollo
* controlador para proceso de coccion de cerveza artesanal
*/

#include "config.h"
#include "encoderControl.h"
#include "uiInicio.h"
#include "temperature.h"
#include "Reloj.h"
#include <TimerOne.h>

void setup() {

  Serial.begin(9600);
  encoder = new ClickEncoder(EN1, EN2, ENC, ENSTP);
  Timer1.initialize(1000);
  Timer1.attachInterrupt(timerIsr);
  last = -1;
  tempManager.init();
  initMenus(menu);
  setTime(10,30,0,11,5,2017); //setTime(hr,min,sec,day,month,yr); 
}

void loop() {
  tempManager.manageTemp();
  manageEncoder();
  updateLCD();
}
