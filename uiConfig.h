#ifndef UICONFIG_H
#define UICONFIG_H

#include "Arduino.h"
#include "uidata.h"

//<MENUS>
#define imAtras 0
#define imOllas 1

void imOllasMenuClick() {
  cli();
  currentUI = UI_CONFIG_OLLAS;
  selMenu = 0;
  sei();
}

void imAtrasMenuClick() {
  cli();
  currentUI = UI_INICIO;
  selMenu = 0;
  sei();
}
//</MENUS>
//<LCD>
void drawTitle() {
  u8g.setColorIndex(1);
  u8g.setFont(FONT_TITLE);
  u8g.setFontPosCenter();
  u8g_uint_t x = (LCDW / 2) - (u8g.getStrWidth("Configuracion") / 2);
  u8g.setPrintPos(x, 4);
  u8g.print("Configuracion");
  u8g.drawRFrame(x - 3, 0, u8g.getStrWidth("Configuracion") + 6, 8, 2);
}

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
    drawTitle();
    drawItem(0, 16, imAtras, "Atras");
    drawItem(0, 24, imOllas, "Ollas");
  } while (u8g.nextPage());
}
//</LCD>
//<INIT>
void uiConfigInit() {
  //<ATRAS>
  mConfig[imAtras].menu.click = imAtrasMenuClick;
  //</ATRAS>
  //<OLLAS>
  mConfig[imOllas].menu.click = imOllasMenuClick;
  //</OLLAS>
} //</INIT>

#endif // UICONFIG_H