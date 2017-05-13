#ifndef UICONTROLL_H
#define UICONTROLL_H

#include "uiSplash.h"
#include "uidata.h"

void initMenus() { uiSplashInit(); }

void updateLCD() {
  switch (currentUI) {
  case UI_SPLASH:
    uiSplashLCD();
    break;
  case UI_INICIO:
    // showInicio();
    break;
  }
  delay(300);
} //</UPDATE LCD>

#endif // UICONTROLL_H