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
      beeper.on();
      if (!isInSubMenu) {
        if (menu[selMenu].menu.held) {
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
      beeper.beep1(150);
      if (isInSubMenu) {
        if (menu[selMenu].subMenu.click) {
          menu[selMenu].subMenu.click();
        }
      } else {
        if (menu[selMenu].menu.click) {
          menu[selMenu].menu.click();
        }
      }
      break;
    case ClickEncoder::DoubleClicked:
      beeper.beep2(150);
      if (isInSubMenu) {
        if (menu[selMenu].subMenu.doubleClick) {
          menu[selMenu].subMenu.doubleClick();
        }
      } else {
        if (menu[selMenu].menu.doubleClick) {
          menu[selMenu].menu.doubleClick();
        }
      }
      break;
    }
  }
}

void manageEncoder() {
  switch (currentUI) {
  case UI_SPLASH:
    procesarEC(mSplash, mSplashTam);
    break;
  case UI_INICIO:
    procesarEC(mInicio, mInicioTam);
    break;
  case UI_CONFIG:
    procesarEC(mConfig,mConfigTam);
    break;
  case UI_CONFIG_OLLAS:
    procesarEC(mConfig,mConfigTam);
    break;
  }
}

#endif // ENCODERMANAGER_H