#ifndef UICONTROLL_H
#define UICONTROLL_H

#include "uiConfig.h"
#include "uiConfigOllas.h"
#include "uiInicio.h"
#include "uiSplash.h"
#include "uiConfigOllasLicor.h"
#include "uiConfigOllasMacerador.h"
#include "uiConfigOllasHervido.h"
#include "uidata.h"
#include "encoderControl.h"

void initMenus() {
  uiSplashInit();
  uiInicioInit();
  uiConfigInit();
  uiConfigOllasInit();
  uiConfigOllasLicorInit();
  uiConfigOllasMaceradorInit();
  uiConfigOllasHervidoInit();
}

void updateLCD() {
  switch (currentUI) {
  case UI_SPLASH:
    procesarEC(mSplash, mSplashTam);
    uiSplashLCD();
    break;
  case UI_INICIO:
    procesarEC(mInicio, mInicioTam);
    uiInicioLCD();
    break;
  case UI_CONFIG:
    procesarEC(mConfig, mConfigTam);
    uiConfigLCD();
    break;
  case UI_CONFIG_OLLAS:
    procesarEC(mConfigOllas, mConfigOllasTam);
    uiConfigOllasLCD();
    break;
  case UI_CONFIG_OLLAS_LICOR:
    procesarEC(mConfigOllasLicor, mConfigOllasLicorTam);
    uiConfigOllasLicorLCD();
    break;
  case UI_CONFIG_OLLAS_MACERADOR:
    procesarEC(mConfigOllasMacerador, mConfigOllasMaceradorTam);
    uiConfigOllasMaceradorLCD();
    break;
  case UI_CONFIG_OLLAS_HERVIDO:
    procesarEC(mConfigOllasHervido, mConfigOllasHervidoTam);
    uiConfigOllasHervidoLCD();
    break;
  }
  delay(300);
} //</UPDATE LCD>

#endif // UICONTROLL_H