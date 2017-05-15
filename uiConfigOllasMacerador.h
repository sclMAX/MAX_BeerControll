#ifndef UICONFIGOLLASMACERADOR_H
#define UICONFIGOLLASMACERADOR_H

#include "Arduino.h"
#include "uidata.h"
#include "uiConfigOllas.h"
#include "utils.h"
#include "uiConfig.h"
#include "uiInicio.h"
//<MENU>
#define imConfigOllasMaceradorAtras 0
#define imConfigOllasMaceradorTempTarget 1
#define imConfigOllasMaceradorHisteresisSup 2
#define imConfigOllasMaceradorHisteresisInf 3
#define imConfigOllasMaceradorAjusteTemperatura 4

void imConfigOllasMaceradorAtrasMenuClick() {
  cli();
  currentUI = UI_CONFIG_OLLAS;
  ecValue = selMenu = 0;
  sei();
}

void imConfigOllasMaceradorHisteresisSupMenuReleased() {
  cli();
  ecValue = (int)tempManager.Macerador.histeresisSup * 100;
  sei();
}

void imConfigOllasMaceradorHisteresisSupSubMenuSelect() {
  cli();
  ecValue = (ecValue >= 0) ? ((ecValue <= 500) ? ecValue : 500) : 0;
  tempManager.Macerador.histeresisSup = (float)ecValue / 100;
  sei();
}

void imConfigOllasMaceradorHisteresisInfMenuReleased() {
  cli();
  ecValue = (int)tempManager.Macerador.histeresisInf * 100;
  sei();
}

void imConfigOllasMaceradorHisteresisInfSubMenuSelect() {
  cli();
  ecValue = (ecValue >= 0) ? ((ecValue <= 500) ? ecValue : 500) : 0;
  tempManager.Macerador.histeresisInf = (float)ecValue / 100;
  sei();
}

void imConfigOllasMaceradorAjusteTemperaturaMenuReleased() {
  cli();
  ecValue = (int)tempManager.Macerador.ajusteTemperatura * 10;
  sei();
}

void imConfigOllasMaceradorAjusteTemperaturaSubMenuSelect() {
  cli();
  ecValue = (ecValue >= -100) ? ((ecValue <= 100) ? ecValue : 100) : -100;
  tempManager.Macerador.ajusteTemperatura = (float)ecValue / 10;
  sei();
}

//</MENU>
//<LCD>

void uiConfigOllasMaceradorLCD() {
  u8g.firstPage();
  do {
    drawTitle(0, "CONFIG OLLA MACERADO");
    drawItem(0, 16, imConfigOllasMaceradorAtras, TXT_ATRAS);
    drawOllaTempTarget(0, 24, imConfigOllasMaceradorTempTarget,
                       tempManager.Macerador);
    drawOllaHisteresisSup(0, 32, imConfigOllasMaceradorHisteresisSup,
                          tempManager.Macerador);
    drawOllaHisteresisInf(0, 40, imConfigOllasMaceradorHisteresisInf,
                          tempManager.Macerador);
    drawOllaAjusteTemperatura(0, 48, imConfigOllasMaceradorAjusteTemperatura,
                              tempManager.Macerador);
  } while (u8g.nextPage());
}
//</LCD>
//<INIT>
void uiConfigOllasMaceradorInit() {

  mConfigOllasMacerador[imConfigOllasMaceradorAtras].menu.click =
      imConfigOllasMaceradorAtrasMenuClick;
  //<TEMP TARGET>
  mConfigOllasMacerador[imConfigOllasMaceradorTempTarget].menu.held =
      MenuHeld; // uiInicio
  mConfigOllasMacerador[imConfigOllasMaceradorTempTarget].menu.released =
      imMaceradorMenuReleased; // uiInicio
  mConfigOllasMacerador[imConfigOllasMaceradorTempTarget].subMenu.select =
      imMaceradorSubMenuSelect; // uiInicio
  mConfigOllasMacerador[imConfigOllasMaceradorTempTarget].subMenu.click =
      SubMenuClick; // uiInicio
  //</TEMP TARGET>
  //<HISTERESIS SUP>
  mConfigOllasMacerador[imConfigOllasMaceradorHisteresisSup].menu.held =
      MenuHeld; // uiInicio
  mConfigOllasMacerador[imConfigOllasMaceradorHisteresisSup].subMenu.click =
      SubMenuClick; // uiInicio
  mConfigOllasMacerador[imConfigOllasMaceradorHisteresisSup].menu.released =
      imConfigOllasMaceradorHisteresisSupMenuReleased;
  mConfigOllasMacerador[imConfigOllasMaceradorHisteresisSup].subMenu.select =
      imConfigOllasMaceradorHisteresisSupSubMenuSelect;
  //</HISTERESIS SUP>
  //<HISTERESIS INF>
  mConfigOllasMacerador[imConfigOllasMaceradorHisteresisInf].menu.held =
      MenuHeld; // uiInicio
  mConfigOllasMacerador[imConfigOllasMaceradorHisteresisInf].subMenu.click =
      SubMenuClick; // uiInicio
  mConfigOllasMacerador[imConfigOllasMaceradorHisteresisInf].menu.released =
      imConfigOllasMaceradorHisteresisInfMenuReleased;
  mConfigOllasMacerador[imConfigOllasMaceradorHisteresisInf].subMenu.select =
      imConfigOllasMaceradorHisteresisInfSubMenuSelect;
  //</HISTERESIS INF>
  //<AJUSTE TEMPERATURA>
  mConfigOllasMacerador[imConfigOllasMaceradorAjusteTemperatura].menu.held =
      MenuHeld; // uiInicio
  mConfigOllasMacerador[imConfigOllasMaceradorAjusteTemperatura].subMenu.click =
      SubMenuClick; // uiInicio
  mConfigOllasMacerador[imConfigOllasMaceradorAjusteTemperatura].menu.released =
      imConfigOllasMaceradorAjusteTemperaturaMenuReleased;
  mConfigOllasMacerador[imConfigOllasMaceradorAjusteTemperatura]
      .subMenu.select = imConfigOllasMaceradorAjusteTemperaturaSubMenuSelect;
  //</AJUSTE TEMPERATURA>
} //</INIT>
#endif // UICONFIGOLLASMACERADOR_H