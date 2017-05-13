#ifndef ENCODERMANAGER_H
#define ENCODERMANAGER_H

#include "Arduino.h"
#include "ClickEncoder.h"
#include "macros.h"
#include "uidata.h"

ClickEncoder *encoder;

void timerIsr() { encoder->service(); }

void enSplash() {
  if (ecValue != ecLast) {
    if (selSubMenu > -1) {
      if (mSplash[selMenu].subMenu[selSubMenu].select) {
        mSplash[selMenu].subMenu[selSubMenu].select();
      }
    } else {
      encoderValue = (ecValue >= 0) ? ((ecValue < COUNT(mSplash)) ? ecValue : 0)
                                    : COUNT(mSplash) - 1;
      selMenu = encoderValue;
      if (mSplash[selMenu].menu.select) {
        mSplash[selMenu].menu.select();
      }
      ecValue = encoderValue;
    }
    ecLast = ecValue;
  }
}

void manageButtons(TMenuItem menu[]) {
  ClickEncoder::Button b = encoder->getButton();
  if (b != ClickEncoder::Open) {
    switch (b) {
    case ClickEncoder::Held:
      beeper.on();
      if (selSubMenu > -1) {
        if (menu[selMenu].subMenu[selSubMenu].held) {
          menu[selMenu].subMenu[selSubMenu].held();
        }
      } else {
        if (menu[selMenu].menu.held) {
          menu[selMenu].menu.held();
        }
      }
      break;
    case ClickEncoder::Released:
      beeper.off();
      if (selSubMenu > -1) {
        if (menu[selMenu].subMenu[selSubMenu].released) {
          menu[selMenu].subMenu[selSubMenu].released();
        }
      } else {
        if (menu[selMenu].menu.released) {
          menu[selMenu].menu.released();
        }
      }
      break;
    case ClickEncoder::Clicked:
      beeper.beep1(150);
      if (selSubMenu > -1) {
        if (menu[selMenu].subMenu[selSubMenu].click) {
          menu[selMenu].subMenu[selSubMenu].click();
        }
      } else {
        if (menu[selMenu].menu.click) {
          menu[selMenu].menu.click();
        }
      }
      break;
    case ClickEncoder::DoubleClicked:
      beeper.beep2(150);
      if (selSubMenu > -1) {
        if (menu[selMenu].subMenu[selSubMenu].doubleClick) {
          menu[selMenu].subMenu[selSubMenu].doubleClick();
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
  ecValue -= encoder->getValue();
  switch (currentUI) {
  case UI_SPLASH:
    enSplash();
    manageButtons(mSplash);
    break;
  }
}

#endif // ENCODERMANAGER_H