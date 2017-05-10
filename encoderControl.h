#ifndef ENCODERMANAGER_H
#define ENCODERMANAGER_H

#include "ClickEncoder.h"
#include "Arduino.h"
#include "menus.h"
#include "beeperControl.h"
#include "pantalla.h"

ClickEncoder *encoder;

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
  }

  ClickEncoder::Button b = encoder->getButton();
  if (b != ClickEncoder::Open) {
    switch (b) {
    case ClickEncoder::Pressed:
      break;
    case ClickEncoder::Held:
      beeper.on();
      if (menu[selMenu].menu.held) {
        menu[selMenu].menu.held();
      }
      break;
    case ClickEncoder::Released:
      beeper.off();
      if (menu[selMenu].menu.released) {
        menu[selMenu].menu.released();
        value = encoderValue;
      }
      break;
    case ClickEncoder::Clicked:
      beeper.beep1(150);
      if (menu[selMenu].menu.click) {
        menu[selMenu].menu.click();
      }
      break;
    case ClickEncoder::DoubleClicked:
      beeper.beep2(150);
      break;
    }
  }
}

#endif // ENCODERMANAGER_H