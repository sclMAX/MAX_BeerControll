#ifndef UICONTROLL_H
#define UICONTROLL_H

#include "uiConfig.h"
#include "uiInicio.h"
#include "uiSplash.h"
#include "uidata.h"

void initMenus() {
  uiSplashInit();
  uiInicioInit();
  uiConfigInit();
}

void updateLCD() {
  switch (currentUI) {
  case UI_SPLASH:
    uiSplashLCD();
    break;
  case UI_INICIO:
    uiInicioLCD();
    break;
  case UI_CONFIG:
    uiConfigLCD();
    break;
  }
  delay(300);
} //</UPDATE LCD>

#endif // UICONTROLL_H