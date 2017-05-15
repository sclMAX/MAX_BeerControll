#ifndef UICONFIG_H
#define UICONFIG_H

#include "Arduino.h"
#include "uidata.h"
#include "configStorage.h"

//<MENUS>
#define imAtrasConfig 0
#define imOllas 1
#define imSaveConfig 2

void imOllasMenuClick() {
  cli();
  currentUI = UI_CONFIG_OLLAS;
  ecValue = selMenu = 0;
  sei();
}

void imAtrasConfigMenuClick() {
  cli();
  currentUI = UI_INICIO;
  ecValue = selMenu = 0;
  sei();
}
//</MENUS>
//<LCD>

void drawItem(u8g_uint_t x, u8g_uint_t y, int item, const char *s) {
  if (item == selMenu) {
    u8g.drawRBox(x, y - 8, LCDW, 8, 1);
    u8g.setColorIndex(0);
  } else {
    u8g.setColorIndex(1);
  }
  u8g.setFont(FONT_CONFIG_ITEM);
  u8g.setFontPosCenter();
  u8g.setPrintPos(x + 2, y - 4);
  u8g.print(s);
}
void uiConfigLCD() {
  u8g.firstPage();
  do {
    // TITULO
    drawTitle(0, "CONFIGURACION"); // y, Texto
    drawItem(0, 16, imAtrasConfig, TXT_ATRAS);
    drawItem(0, 24, imOllas, "OLLAS");
    drawItem(0, 56, imSaveConfig, "GUARDAR CONFIGURACION");
  } while (u8g.nextPage());
}
//</LCD>
//<INIT>
void uiConfigInit() {
  mConfig[imAtrasConfig].menu.click = imAtrasConfigMenuClick;
  mConfig[imOllas].menu.click = imOllasMenuClick;
  mConfig[imSaveConfig].menu.click = saveConfig;
} //</INIT>

#endif // UICONFIG_H