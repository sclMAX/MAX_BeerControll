#ifndef UICONTROLL_H
#define UICONTROLL_H

#include "uiInicio.h"
#include "uiSplash.h"
#include "uidata.h"

void initMenus() {
  uiSplashInit();
  uiInicioInit();
}

void updateLCD() {
  switch (currentUI) {
  case UI_SPLASH:
    uiSplashLCD();
    break;
  case UI_INICIO:
    uiInicioLCD();
    break;
  }
  delay(300);
} //</UPDATE LCD>

#endif // UICONTROLL_H