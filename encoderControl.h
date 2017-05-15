#ifndef ENCODERMANAGER_H
#define ENCODERMANAGER_H

#include "Arduino.h"
#include "ClickEncoder.h"
#include "macros.h"
#include "uidata.h"

ClickEncoder *encoder;

void timerIsr() { encoder->service(); }

void procesarEC(TMenuItem menu[], int tam) {
  ecValue -= encoder->getValue();
  if (ecValue != ecLast) {
    if (isInSubMenu) {
      if (menu[selMenu].subMenu.select)
        menu[selMenu].subMenu.select();
    } else {
      cli();
      encoderValue = ecValue;
      encoderValue = (encoderValue >= 0)
                         ? ((encoderValue < tam) ? encoderValue : 0)
                         : (tam - 1);
      selMenu = encoderValue;
      ecValue = encoderValue;
      sei();
    }
    ecLast = ecValue;
  }
  ClickEncoder::Button b = encoder->getButton();
  if (b != ClickEncoder::Open) {
    switch (b) {
    case ClickEncoder::Held:
      if (!isInSubMenu) {
        if (menu[selMenu].menu.held) {
          beeper.on();
          menu[selMenu].menu.held();
        }
      }
      break;
    case ClickEncoder::Released:
      beeper.off();
      if (menu[selMenu].menu.released) {
        menu[selMenu].menu.released();
      }
      break;
    case ClickEncoder::Clicked:
      if (isInSubMenu) {
        if (menu[selMenu].subMenu.click) {
          beeper.beep1(100);
          menu[selMenu].subMenu.click();
        }
      } else {
        if (menu[selMenu].menu.click) {
          beeper.beep1(100);
          menu[selMenu].menu.click();
        }
      }
      break;
    case ClickEncoder::DoubleClicked:
      beeper.beep2(150);
      if (isInSubMenu) {
        if (menu[selMenu].subMenu.doubleClick) {
          beeper.beep2(150);
          menu[selMenu].subMenu.doubleClick();
        }
      } else {
        if (menu[selMenu].menu.doubleClick) {
          beeper.beep2(150);
          menu[selMenu].menu.doubleClick();
        }
      }
      break;
    }
  }
}

#endif // ENCODERMANAGER_H