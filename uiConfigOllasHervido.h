#ifndef UICONFIGOLLASHERVIDO_H
#define UICONFIGOLLASHERVIDO_H

#include "Arduino.h"
#include "uidata.h"
#include "uiConfigOllas.h"
#include "utils.h"
#include "uiConfig.h"
#include "uiInicio.h"
//<MENU>
#define imConfigOllasHervidoAtras 0
#define imConfigOllasHervidoTempTarget 1
#define imConfigOllasHervidoHisteresisSup 2
#define imConfigOllasHervidoHisteresisInf 3
#define imConfigOllasHervidoAjusteTemperatura 4

void imConfigOllasHervidoAtrasMenuClick() {
  cli();
  currentUI = UI_CONFIG_OLLAS;
  ecValue = selMenu = 0;
  sei();
}

void imConfigOllasHervidoHisteresisSupMenuReleased() {
  cli();
  ecValue = (int)tempManager.Hervido.histeresisSup * 100;
  sei();
}

void imConfigOllasHervidoHisteresisSupSubMenuSelect() {
  cli();
  ecValue = (ecValue >= 0) ? ((ecValue <= 500) ? ecValue : 500) : 0;
  tempManager.Hervido.histeresisSup = (float)ecValue / 100;
  sei();
}

void imConfigOllasHervidoHisteresisInfMenuReleased() {
  cli();
  ecValue = (int)tempManager.Hervido.histeresisInf * 100;
  sei();
}

void imConfigOllasHervidoHisteresisInfSubMenuSelect() {
  cli();
  ecValue = (ecValue >= 0) ? ((ecValue <= 500) ? ecValue : 500) : 0;
  tempManager.Hervido.histeresisInf = (float)ecValue / 100;
  sei();
}

void imConfigOllasHervidoAjusteTemperaturaMenuReleased() {
  cli();
  ecValue = (int)tempManager.Hervido.ajusteTemperatura * 10;
  sei();
}

void imConfigOllasHervidoAjusteTemperaturaSubMenuSelect() {
  cli();
  ecValue = (ecValue >= -100) ? ((ecValue <= 100) ? ecValue : 100) : -100;
  tempManager.Hervido.ajusteTemperatura = (float)ecValue / 10;
  sei();
}

//</MENU>
//<LCD>

void uiConfigOllasHervidoLCD() {
  u8g.firstPage();
  do {
    drawTitle(0, "CONFIG OLLA HERVIDO");
    drawItem(0, 16, imConfigOllasHervidoAtras, TXT_ATRAS);
    drawOllaTempTarget(0, 24, imConfigOllasHervidoTempTarget, tempManager.Hervido);
    drawOllaHisteresisSup(0, 32, imConfigOllasHervidoHisteresisSup,
                          tempManager.Hervido);
    drawOllaHisteresisInf(0, 40, imConfigOllasHervidoHisteresisInf,
                          tempManager.Hervido);
    drawOllaAjusteTemperatura(0, 48, imConfigOllasHervidoAjusteTemperatura,
                              tempManager.Hervido);
  } while (u8g.nextPage());
}
//</LCD>
//<INIT>
void uiConfigOllasHervidoInit() {

  mConfigOllasHervido[imConfigOllasHervidoAtras].menu.click =
      imConfigOllasHervidoAtrasMenuClick;
  //<TEMP TARGET>
  mConfigOllasHervido[imConfigOllasHervidoTempTarget].menu.held =
      MenuHeld; // uiInicio
  mConfigOllasHervido[imConfigOllasHervidoTempTarget].menu.released =
      imHervidoMenuReleased; // uiInicio
  mConfigOllasHervido[imConfigOllasHervidoTempTarget].subMenu.select =
      imHervidoSubMenuSelect; // uiInicio
  mConfigOllasHervido[imConfigOllasHervidoTempTarget].subMenu.click =
      SubMenuClick; // uiInicio
  //</TEMP TARGET>
  //<HISTERESIS SUP>
  mConfigOllasHervido[imConfigOllasHervidoHisteresisSup].menu.held =
      MenuHeld; // uiInicio
  mConfigOllasHervido[imConfigOllasHervidoHisteresisSup].subMenu.click =
      SubMenuClick; // uiInicio
  mConfigOllasHervido[imConfigOllasHervidoHisteresisSup].menu.released =
      imConfigOllasHervidoHisteresisSupMenuReleased;
  mConfigOllasHervido[imConfigOllasHervidoHisteresisSup].subMenu.select =
      imConfigOllasHervidoHisteresisSupSubMenuSelect;
  //</HISTERESIS SUP>
  //<HISTERESIS INF>
  mConfigOllasHervido[imConfigOllasHervidoHisteresisInf].menu.held =
      MenuHeld; // uiInicio
  mConfigOllasHervido[imConfigOllasHervidoHisteresisInf].subMenu.click =
      SubMenuClick; // uiInicio
  mConfigOllasHervido[imConfigOllasHervidoHisteresisInf].menu.released =
      imConfigOllasHervidoHisteresisInfMenuReleased;
  mConfigOllasHervido[imConfigOllasHervidoHisteresisInf].subMenu.select =
      imConfigOllasHervidoHisteresisInfSubMenuSelect;
  //</HISTERESIS INF>
  //<AJUSTE TEMPERATURA>
  mConfigOllasHervido[imConfigOllasHervidoAjusteTemperatura].menu.held =
      MenuHeld; // uiInicio
  mConfigOllasHervido[imConfigOllasHervidoAjusteTemperatura].subMenu.click =
      SubMenuClick; // uiInicio
  mConfigOllasHervido[imConfigOllasHervidoAjusteTemperatura].menu.released =
      imConfigOllasHervidoAjusteTemperaturaMenuReleased;
  mConfigOllasHervido[imConfigOllasHervidoAjusteTemperatura].subMenu.select =
      imConfigOllasHervidoAjusteTemperaturaSubMenuSelect;
  //</AJUSTE TEMPERATURA>
} //</INIT>
#endif // UICONFIGOLLASHERVIDO_H