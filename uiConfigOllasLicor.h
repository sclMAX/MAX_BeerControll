#ifndef UICONFIGOLLASLICOR_H
#define UICONFIGOLLASLICOR_H

#include "Arduino.h"
#include "uidata.h"
#include "uiConfigOllas.h"
#include "utils.h"
#include "uiConfig.h"
#include "uiInicio.h"
//<MENU>
#define imConfigOllasLicorAtras 0
#define imConfigOllasLicorTempTarget 1
#define imConfigOllasLicorHisteresisSup 2
#define imConfigOllasLicorHisteresisInf 3
#define imConfigOllasLicorAjusteTemperatura 4

void imConfigOllasLicorAtrasMenuClick() {
  cli();
  currentUI = UI_CONFIG_OLLAS;
  ecValue = selMenu = 0;
  sei();
}

void imConfigOllasLicorHisteresisSupMenuReleased() {
  cli();
  ecValue = (int)tempManager.Licor.histeresisSup * 100;
  sei();
}

void imConfigOllasLicorHisteresisSupSubMenuSelect() {
  cli();
  ecValue = (ecValue >= 0) ? ((ecValue <= 500) ? ecValue : 500) : 0;
  tempManager.Licor.histeresisSup = (float)ecValue / 100;
  sei();
}

void imConfigOllasLicorHisteresisInfMenuReleased() {
  cli();
  ecValue = (int)tempManager.Licor.histeresisInf * 100;
  sei();
}

void imConfigOllasLicorHisteresisInfSubMenuSelect() {
  cli();
  ecValue = (ecValue >= 0) ? ((ecValue <= 500) ? ecValue : 500) : 0;
  tempManager.Licor.histeresisInf = (float)ecValue / 100;
  sei();
}

void imConfigOllasLicorAjusteTemperaturaMenuReleased() {
  cli();
  ecValue = (int)tempManager.Licor.ajusteTemperatura * 10;
  sei();
}

void imConfigOllasLicorAjusteTemperaturaSubMenuSelect() {
  cli();
  ecValue = (ecValue >= -100) ? ((ecValue <= 100) ? ecValue : 100) : -100;
  tempManager.Licor.ajusteTemperatura = (float)ecValue / 10;
  sei();
}

//</MENU>
//<LCD>

void uiConfigOllasLicorLCD() {
  u8g.firstPage();
  do {
    drawTitle(0, "CONFIG OLLA LICOR");
    drawItem(0, 16, imConfigOllasLicorAtras, TXT_ATRAS);
    drawOllaTempTarget(0, 24, imConfigOllasLicorTempTarget, tempManager.Licor);
    drawOllaHisteresisSup(0, 32, imConfigOllasLicorHisteresisSup,
                          tempManager.Licor);
    drawOllaHisteresisInf(0, 40, imConfigOllasLicorHisteresisInf,
                          tempManager.Licor);
    drawOllaAjusteTemperatura(0, 48, imConfigOllasLicorAjusteTemperatura,
                              tempManager.Licor);
  } while (u8g.nextPage());
}
//</LCD>
//<INIT>
void uiConfigOllasLicorInit() {

  mConfigOllasLicor[imConfigOllasLicorAtras].menu.click =
      imConfigOllasLicorAtrasMenuClick;
  //<TEMP TARGET>
  mConfigOllasLicor[imConfigOllasLicorTempTarget].menu.held =
      MenuHeld; // uiInicio
  mConfigOllasLicor[imConfigOllasLicorTempTarget].menu.released =
      imLicorMenuReleased; // uiInicio
  mConfigOllasLicor[imConfigOllasLicorTempTarget].subMenu.select =
      imLicorSubMenuSelect; // uiInicio
  mConfigOllasLicor[imConfigOllasLicorTempTarget].subMenu.click =
      SubMenuClick; // uiInicio
  //</TEMP TARGET>
  //<HISTERESIS SUP>
  mConfigOllasLicor[imConfigOllasLicorHisteresisSup].menu.held =
      MenuHeld; // uiInicio
  mConfigOllasLicor[imConfigOllasLicorHisteresisSup].subMenu.click =
      SubMenuClick; // uiInicio
  mConfigOllasLicor[imConfigOllasLicorHisteresisSup].menu.released =
      imConfigOllasLicorHisteresisSupMenuReleased;
  mConfigOllasLicor[imConfigOllasLicorHisteresisSup].subMenu.select =
      imConfigOllasLicorHisteresisSupSubMenuSelect;
  //</HISTERESIS SUP>
  //<HISTERESIS INF>
  mConfigOllasLicor[imConfigOllasLicorHisteresisInf].menu.held =
      MenuHeld; // uiInicio
  mConfigOllasLicor[imConfigOllasLicorHisteresisInf].subMenu.click =
      SubMenuClick; // uiInicio
  mConfigOllasLicor[imConfigOllasLicorHisteresisInf].menu.released =
      imConfigOllasLicorHisteresisInfMenuReleased;
  mConfigOllasLicor[imConfigOllasLicorHisteresisInf].subMenu.select =
      imConfigOllasLicorHisteresisInfSubMenuSelect;
  //</HISTERESIS INF>
  //<AJUSTE TEMPERATURA>
  mConfigOllasLicor[imConfigOllasLicorAjusteTemperatura].menu.held =
      MenuHeld; // uiInicio
  mConfigOllasLicor[imConfigOllasLicorAjusteTemperatura].subMenu.click =
      SubMenuClick; // uiInicio
  mConfigOllasLicor[imConfigOllasLicorAjusteTemperatura].menu.released =
      imConfigOllasLicorAjusteTemperaturaMenuReleased;
  mConfigOllasLicor[imConfigOllasLicorAjusteTemperatura].subMenu.select =
      imConfigOllasLicorAjusteTemperaturaSubMenuSelect;
  //</AJUSTE TEMPERATURA>
} //</INIT>
#endif // UICONFIGOLLASLICOR_H