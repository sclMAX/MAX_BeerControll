#ifndef ENCODERMANAGER_H
#define ENCODERMANAGER_H

#include "Arduino.h"
#include "ClickEncoder.h"
#include "uidata.h"
#include "menus.h"
#include "pantalla.h"

ClickEncoder *encoder;

void timerIsr() { encoder->service(); }

void manageEncoder() {
  encoderValue -= encoder->getValue();
  
  if (encoderValue != encoderLast) {
    if (selSubMenu > -1) {
      if (COUNT(currentMenu[selMenu].subMenu) > 1) {
        encoderValue =
            (encoderValue >= 0)
                ? ((encoderValue < COUNT(currentMenu[selMenu].subMenu))
                       ? encoderValue
                       : 0)
                : COUNT(currentMenu[selMenu].subMenu) - 1;
        selSubMenu = encoderValue;
      }
      if (currentMenu[selMenu].subMenu[selSubMenu].select) {
        currentMenu[selMenu].subMenu[selSubMenu].select();
      }
    } else {
      encoderValue =
          (encoderValue >= 0)
              ? ((encoderValue < COUNT(currentMenu)) ? encoderValue : 0)
              : COUNT(currentMenu) - 1;
      selMenu = encoderValue;
      if (menu[selMenu].menu.select) {
        menu[selMenu].menu.select();
      }
    }
    encoderLast = encoderValue;
  }

  ClickEncoder::Button b = encoder->getButton();
  if (b != ClickEncoder::Open) {
    switch (b) {
    case ClickEncoder::Held:
      beeper.on();
      if (selSubMenu > -1) {
        if (currentMenu[selMenu].subMenu[selSubMenu].held) {
          currentMenu[selMenu].subMenu[selSubMenu].held();
        }
      } else {
        if (currentMenu[selMenu].menu.held) {
          currentMenu[selMenu].menu.held();
        }
      }
      break;
    case ClickEncoder::Released:
      beeper.off();
      if (selSubMenu > -1) {
        if (currentMenu[selMenu].subMenu[selSubMenu].released) {
          currentMenu[selMenu].subMenu[selSubMenu].released();
        }
      } else {
        if (currentMenu[selMenu].menu.released) {
          currentMenu[selMenu].menu.released();
        }
      }
      break;
    case ClickEncoder::Clicked:
      beeper.beep1(150);
      if (selSubMenu > -1) {
        if (currentMenu[selMenu].subMenu[selSubMenu].click) {
          currentMenu[selMenu].subMenu[selSubMenu].click();
        }
      } else {
        if (currentMenu[selMenu].menu.click) {
          currentMenu[selMenu].menu.click();
        }
      }
      break;
    case ClickEncoder::DoubleClicked:
      beeper.beep2(150);
      if (selSubMenu > -1) {
        if (currentMenu[selMenu].subMenu[selSubMenu].doubleClick) {
          currentMenu[selMenu].subMenu[selSubMenu].doubleClick();
        }
      } else {
        if (currentMenu[selMenu].menu.doubleClick) {
          currentMenu[selMenu].menu.doubleClick();
        }
      }
      break;
    }
  }
}

#endif // ENCODERMANAGER_H