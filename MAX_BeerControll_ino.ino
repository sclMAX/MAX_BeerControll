/*
* Beer Control v1.0 by MAX
* 2017-05-07 inicio desarrollo
* controlador para proceso de coccion de cerveza artesanal
*/
#include "ClickEncoder.h"
#include "buzzer.h"
#include "config.h"
#include "macros.h"
#include "menus.h"
#include "pantalla.h"
#include "temperature.h"
#include <TimerOne.h>

ClickEncoder *encoder;
Buzzer buzzer;
TMenuItem menu[3];

int16_t last, value, selMenu;

void timerIsr() { encoder->service(); }

void manageEncoder() {
  value -= encoder->getValue();
  if (value != last) {
    if (isSubMenuOlla) {
      if (encoderValue != value) {
        encoderValue = value;
        menu[selMenu].subMenu[0].select();
      }
    } else {
      value = (value >= 0) ? value : 0;
      value = (value <= COUNT(menu) - 1) ? value : COUNT(menu) - 1;
      selMenu = value;
      menu[value].menu.select();
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
      Serial.println("ClickEncoder::Held");
      if (menu[selMenu].menu.held) {
        menu[selMenu].menu.held();
      }
      break;
    case ClickEncoder::Released:
      Serial.println("ClickEncoder::Released");
      if (menu[selMenu].menu.released) {
        menu[selMenu].menu.released();
        value = encoderValue;
      }
      break;
    case ClickEncoder::Clicked:
      Serial.println("ClickEncoder::Clicked");
      if (menu[selMenu].menu.click) {
        menu[selMenu].menu.click();
      }
      break;
    case ClickEncoder::DoubleClicked:
      Serial.println("ClickEncoder::DoubleClicked");
      //   buzzer.tone(2, 5000);
      //   buzzer.tone(2, 5000);
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
