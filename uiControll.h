#ifndef UICONTROLL_H
#define UICONTROLL_H

#include "uiConfig.h"
#include "uiConfigOllas.h"
#include "uiInicio.h"
#include "uiSplash.h"
#include "uidata.h"

void initMenus() {
  uiSplashInit();
  uiInicioInit();
  uiConfigInit();
  uiConfigOllasInit();
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
  case UI_CONFIG_OLLAS:
    uiConfigOllasLCD();
    break;
  }
  delay(300);
} //</UPDATE LCD>

#endif // UICONTROLL_H