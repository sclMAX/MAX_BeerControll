/*
* Beer Control v1.0 by MAX
* 2017-05-07 inicio desarrollo
* controlador para proceso de coccion de cerveza artesanal
*/
#include "Reloj.h"
#include "config.h"
#include "encoderControl.h"
#include "temperature.h"
#include "uiControll.h"
#include "uidata.h"
#include <TimerOne.h>
#include "configStorage.h"

void setup()
{

  Serial.begin(9600);
  initMenus();
  encoder = new ClickEncoder(EN1, EN2, ENC, ENSTP);
  Timer1.initialize(1000);
  Timer1.attachInterrupt(timerIsr);
  readConfig();
  tempManager.init();
}

void loop()
{
  tempManager.manageTemp();
  updateLCD();
}
