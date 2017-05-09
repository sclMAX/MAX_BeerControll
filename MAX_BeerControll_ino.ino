/*
* Beer Control v1.0 by MAX
* 2017-05-07 inicio desarrollo
* controlador para proceso de coccion de cerveza artesanal
*/
#include "ClickEncoder.h"
#include "config.h"
#include "macros.h"
#include "menus.h"
#include "pantalla.h"
#include "temperature.h"
#include "beeperControl.h"
#include <TimerOne.h>

ClickEncoder *encoder;
TMenuItem menu[3];

int16_t last, value;

void timerIsr() { encoder->service(); }

void manageEncoder() {
  value -= encoder->getValue();
  if (value != last) {
    if (selSubMenu > -1) {
      if (encoderValue != value) {
        encoderValue = value;
        if (menu[selMenu].subMenu[selSubMenu].select) {
          menu[selMenu].subMenu[selSubMenu].select();
          value = encoderValue;
        }
      }
    } else {
      value = (value >= 0) ? value : COUNT(menu) - 1;
      value = (value <= COUNT(menu) - 1) ? value : 0;
      selMenu = value;
      if (menu[selMenu].menu.select) {
        menu[selMenu].menu.select();
        value = selMenu;
      }
    }
    last = value;
    Serial.print("Encoder Value: ");
    Serial.println(value);
  }

  ClickEncoder::Button b = encoder->getButton();
  if (b != ClickEncoder::Open) {
    switch (b) {
    case ClickEncoder::Pressed:
      break;
    case ClickEncoder::Held:
      beeper.on();
      Serial.println("ClickEncoder::Held");
      if (menu[selMenu].menu.held) {
        menu[selMenu].menu.held();
      }
      break;
    case ClickEncoder::Released:
      beeper.off();
      Serial.println("ClickEncoder::Released");
      if (menu[selMenu].menu.released) {
        menu[selMenu].menu.released();
        value = encoderValue;
      }
      break;
    case ClickEncoder::Clicked:
      beeper.beep1(150);
      Serial.println("ClickEncoder::Clicked");
      if (menu[selMenu].menu.click) {
        menu[selMenu].menu.click();
      }
      break;
    case ClickEncoder::DoubleClicked:
      beeper.beep2(150);
      Serial.println("ClickEncoder::DoubleClicked");
      encoder->setAccelerationEnabled(!encoder->getAccelerationEnabled());
      Serial.print("  Acceleration is ");
      Serial.println((encoder->getAccelerationEnabled()) ? "enabled"
                                                         : "disabled");
      break;
    }
  }
}

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
