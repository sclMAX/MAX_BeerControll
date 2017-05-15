#ifndef UICONFIGOLLAS_H
#define UICONFIGOLLAS_H

#include "Arduino.h"
#include "uidata.h"
#include "temperature.h"
#include "utils.h"

//<MENU>
#define imAtrasConfigOllas 0
#define imOllaLicor 1
#define imOllaMacerador 2
#define imOllaHervido 3

void imAtrasConfigOllasMenuClick() {
  cli();
  currentUI = UI_CONFIG;
  ecValue = selMenu = 0;
  sei();
}

void imOllaLicorMenuClick() {
  cli();
  currentUI = UI_CONFIG_OLLAS_LICOR;
  ecValue = selMenu = 0;
  sei();
}

void imOllaMaceradorMenuClick() {
  cli();
  currentUI = UI_CONFIG_OLLAS_MACERADOR;
  ecValue = selMenu = 0;
  sei();
}

void imOllaHervidoMenuClick() {
  cli();
  currentUI = UI_CONFIG_OLLAS_HERVIDO;
  ecValue = selMenu = 0;
  sei();
}
//</MENU>
//<LCD>
void drawOllaTempTarget(u8g_uint_t x, u8g_uint_t y, int item, Olla &olla) {
  if ((item == selMenu) && (!isInSubMenu)) {
    u8g.drawRBox(x, y - 8, LCDW, 8, 1);
    u8g.setColorIndex(0);
  } else {
    u8g.setColorIndex(1);
  }
  u8g.setFont(FONT_CONFIG_ITEM);
  u8g.setFontPosCenter();
  u8g.setPrintPos(x + 2, y - 4);
  u8g.print("TEMPERATURA:");
  u8g_uint_t tw = u8g.getStrWidth(ftostr3(olla.tempTarget));
  if ((isInSubMenu) && (item == selMenu)) {
    u8g.drawBox(LCDW - (tw + 4), y - 8, (tw + 4), 8);
    u8g.setColorIndex(0);
  }
  u8g.setPrintPos(LCDW - (tw + 2), y - 4);
  u8g.print(ftostr3(olla.tempTarget));
  u8g.setColorIndex(1);
}

void drawOllaHisteresisSup(u8g_uint_t x, u8g_uint_t y, int item, Olla &olla) {
  if ((item == selMenu) && (!isInSubMenu)) {
    u8g.drawRBox(x, y - 8, LCDW, 8, 1);
    u8g.setColorIndex(0);
  } else {
    u8g.setColorIndex(1);
  }
  u8g.setFont(FONT_CONFIG_ITEM);
  u8g.setFontPosCenter();
  u8g.setPrintPos(x + 2, y - 4);
  u8g.print("HISTERESIS SUP:");
  u8g_uint_t tw = u8g.getStrWidth(ftostr12ns(olla.histeresisSup));
  if ((isInSubMenu) && (item == selMenu)) {
    u8g.drawBox(LCDW - (tw + 4), y - 8, (tw + 4), 8);
    u8g.setColorIndex(0);
  }
  u8g.setPrintPos(LCDW - (tw + 2), y - 4);
  u8g.print(ftostr12ns(olla.histeresisSup));
  u8g.setColorIndex(1);
}

void drawOllaHisteresisInf(u8g_uint_t x, u8g_uint_t y, int item, Olla &olla) {
  if ((item == selMenu) && (!isInSubMenu)) {
    u8g.drawRBox(x, y - 8, LCDW, 8, 1);
    u8g.setColorIndex(0);
  } else {
    u8g.setColorIndex(1);
  }
  u8g.setFont(FONT_CONFIG_ITEM);
  u8g.setFontPosCenter();
  u8g.setPrintPos(x + 2, y - 4);
  u8g.print("HISTERESIS INF:");
  u8g_uint_t tw = u8g.getStrWidth(ftostr12ns(olla.histeresisInf));
  if ((isInSubMenu) && (item == selMenu)) {
    u8g.drawBox(LCDW - (tw + 4), y - 8, (tw + 4), 8);
    u8g.setColorIndex(0);
  }
  u8g.setPrintPos(LCDW - (tw + 2), y - 4);
  u8g.print(ftostr12ns(olla.histeresisInf));
  u8g.setColorIndex(1);
}

void drawOllaAjusteTemperatura(u8g_uint_t x, u8g_uint_t y, int item,
                               Olla &olla) {
  if ((item == selMenu) && (!isInSubMenu)) {
    u8g.drawRBox(x, y - 8, LCDW, 8, 1);
    u8g.setColorIndex(0);
  } else {
    u8g.setColorIndex(1);
  }
  u8g.setFont(FONT_CONFIG_ITEM);
  u8g.setFontPosCenter();
  u8g.setPrintPos(x + 2, y - 4);
  u8g.print("AJUSTE TEMP.:");
  u8g_uint_t tw = u8g.getStrWidth(ftostr32(olla.ajusteTemperatura));
  if ((isInSubMenu) && (item == selMenu)) {
    u8g.drawBox(LCDW - (tw + 4), y - 8, (tw + 4), 8);
    u8g.setColorIndex(0);
  }
  u8g.setPrintPos(LCDW - (tw + 2), y - 4);
  u8g.print(ftostr32(olla.ajusteTemperatura));
  u8g.setColorIndex(1);
}

void uiConfigOllasLCD() {
  u8g.firstPage();
  do {
    // TITULO
    drawTitle(0, "CONFIG. OLLAS");
    drawItem(0, 16, imAtrasConfigOllas, TXT_ATRAS);
    drawItem(0, 24, imOllaLicor, "OLLA LICOR");
    drawItem(0, 32, imOllaMacerador, "OLLA MACERADO");
    drawItem(0, 40, imOllaHervido, "OLLA HERVIDO");
  } while (u8g.nextPage());
}
//</LCD>
//<INIT>
void uiConfigOllasInit() {
  mConfigOllas[imAtrasConfigOllas].menu.click = imAtrasConfigOllasMenuClick;
  mConfigOllas[imOllaLicor].menu.click = imOllaLicorMenuClick;
  mConfigOllas[imOllaMacerador].menu.click = imOllaMaceradorMenuClick;
  mConfigOllas[imOllaHervido].menu.click = imOllaHervidoMenuClick;
} //</INIT>

#endif // UICONFIGOLLAS_H