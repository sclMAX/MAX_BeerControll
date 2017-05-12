#ifndef UISPLASH_H
#define UISPLASH_H

#include "Arduino.h"
#include "uidata.h"
#include "Reloj.h"

//<MENU>
#define ITEMS 6
#define imDia 0
#define imMes 1
#define imAnio 2
#define imHora 3
#define imMinuto 4
#define imBtnInicio 5

//<COMUN>
void imSubMenuClick() {
  selSubMenu = -1;
  encoderValue = selMenu;
};
void imMenuHeld() { selSubMenu = 0; };
//</COMUN>
//<DIA>
void imDiaSubMenuSelect() {
  encoderValue =
      (encoderValue >= 1) ? ((encoderValue <= 31) ? encoderValue : 1) : 31;
  setTime(hour(), minute(), second(), encoderValue, month(),
          year()); // setTime(hr,min,sec,day,month,yr);
};
void imDiaMenuReleased() { encoderValue = day(); };
//</DIA>
//<MES>
void imMesSubMenuSelect() {
  encoderValue =
      (encoderValue >= 1) ? ((encoderValue <= 12) ? encoderValue : 1) : 12;
  setTime(hour(), minute(), second(), day(), encoderValue,
          year()); // setTime(hr,min,sec,day,month,yr);
};
void imMesMenuReleased() { encoderValue = month(); };
//</MES>
//<AÑO>
void imAnioSubMenuSelect() {
  encoderValue = (encoderValue >= 1970) ? encoderValue : 1970;
  setTime(hour(), minute(), second(), day(), month(),
          encoderValue); // setTime(hr,min,sec,day,month,yr);
};
void imAnioMenuReleased() { encoderValue = year(); };
//</AÑO>
//<HORA>
void imHoraSubMenuSelect() {
  encoderValue =
      (encoderValue >= 0) ? ((encoderValue <= 23) ? encoderValue : 0) : 23;
  setTime(encoderValue, minute(), second(), day(), month(),
          year()); // setTime(hr,min,sec,day,month,yr);
};
void imHoraMenuReleased() { encoderValue = hour(); };
//</HORA>
//<MINUTO>
void imMinutoSubMenuSelect() {
  encoderValue =
      (encoderValue >= 0) ? ((encoderValue <= 59) ? encoderValue : 0) : 59;
  setTime(hour(), encoderValue, second(), day(), month(),
          year()); // setTime(hr,min,sec,day,month,yr);
};
void imMinutoMenuReleased() { encoderValue = minute(); };
//</MINUTO>
//<BTNINICIO>
void imBtnInicioClick() { currentUI = UI_INICIO; }
//</BTNINICIO>

void uiSplashInit() { //<INIT>
  if (currentMenu != 0) {
    delete[] currentMenu;
  }
  currentMenu = new TMenuItem[ITEMS];
  //<DIA>
  currentMenu[imDia].subMenu[0].select = imDiaSubMenuSelect;
  currentMenu[imDia].subMenu[0].click = imSubMenuClick;
  currentMenu[imDia].menu.held = imMenuHeld;
  currentMenu[imDia].menu.released = imDiaMenuReleased;
  //</DIA>
  //<MES>
  currentMenu[imMes].subMenu[0].select = imMesSubMenuSelect;
  currentMenu[imMes].subMenu[0].click = imSubMenuClick;
  currentMenu[imMes].menu.held = imMenuHeld;
  currentMenu[imMes].menu.released = imMesMenuReleased;
  //</MES>
  //<AÑO>
  currentMenu[imAnio].subMenu[0].select = imAnioSubMenuSelect;
  currentMenu[imAnio].subMenu[0].click = imSubMenuClick;
  currentMenu[imAnio].menu.held = imMenuHeld;
  currentMenu[imAnio].menu.released = imAnioMenuReleased;
  //</AÑO>
  //<HORA>
  currentMenu[imHora].subMenu[0].select = imHoraSubMenuSelect;
  currentMenu[imHora].subMenu[0].click = imSubMenuClick;
  currentMenu[imHora].menu.held = imMenuHeld;
  currentMenu[imHora].menu.released = imHoraMenuReleased;
  //</HORA>
  //<MINUTO>
  currentMenu[imMinuto].subMenu[0].select = imMinutoSubMenuSelect;
  currentMenu[imMinuto].subMenu[0].click = imSubMenuClick;
  currentMenu[imMinuto].menu.held = imMenuHeld;
  currentMenu[imMinuto].menu.released = imMinutoMenuReleased;
  //</MINUTO>
  //<BTNINICIO>

  //</BTNINICIO>
  selMenu = 0;
  selSubMenu = -1;
} //</INIT>
//</MENU>
//<LCD DRAW>
//<DRAW FECHA>
void insertSeparador(u8g_uint_t &x, u8g_uint_t &y, u8g_uint_t &m, char *s) {
  u8g_uint_t tw;
  u8g.setColorIndex(1);
  tw = u8g.getStrWidth(s);
  u8g.setPrintPos(x, y - m / 2);
  u8g.print(s);
  x = x + tw + m;
  return tw;
}

void insertTime(u8g_uint_t &x, u8g_uint_t &y, u8g_uint_t &m, int16_t item,
                char *s) {
  u8g_uint_t th;
  u8g_uint_t tw;
  tw = u8g.getStrWidth(s);
  th = u8g.getFontAscent() - u8g.getFontDescent();
  if (selMenu == item) {
    if ((selSubMenu == 0)) {
      u8g.drawBox(x, y, tw + m, th + m);
      u8g.setColorIndex(0);
    } else {
      u8g.drawFrame(x, y, tw + m, th + m);
    }
  }
  u8g.setPrintPos(x + m / 2, y - m / 2); // pos dentro del marco
  u8g.print(s);
  x = x + tw + 2 * m;
  u8g.setColorIndex(1);
}

void drawFecha(u8g_uint_t x, u8g_uint_t y) {
  u8g_uint_t m = 2;
  u8g.setColorIndex(1);
  u8g.setFont(FONT_FECHA);
  u8g.setFontPosTop();
  insertTime(x, y, m, imDia, diaStr());       // Dia
  insertSeparador(x, y, m, SEPARADOR_FECHA);  // Separador /
  insertTime(x, y, m, imMes, mesStr());       // Mes
  insertSeparador(x, y, m, SEPARADOR_FECHA);  // Separador /
  insertTime(x, y, m, imMes, anioStr());      // Año
  insertSeparador(x, y, m, " ");              // Separador /
  insertTime(x, y, m, imHora, horaStr());     // Hora
  insertSeparador(x, y, m, SEPARADOR_HORA);   // Separador /
  insertTime(x, y, m, imMinuto, minutoStr()); // Minuto
} //</DRAW FECHA>

void uiSplashLCD() {
  u8g.firstPage();
  do {
    u8g_uint_t logoHeight = 41;
    u8g.drawBitmapP(0, 0, LOGO_WIDTH, LOGO_HEIGHT, logo);
    u8g.setColorIndex(1);
    u8g.setFont(FONT_VERSION);
    u8g.setFontPosTop();
    u8g.drawStr((u8g.getWidth() - (u8g.getStrWidth(VERSION))), (logoHeight + 1),
                VERSION);
    drawFecha(1, (logoHeight + 10));
    u8g.setFont(FONT_ETIQUETA);
    u8g.setFontPosBottom();
    u8g_uint_t x = u8g.getWidth() - (u8g.getStrWidth("INICIO") + 4) - 2;
    u8g_uint_t y =
        u8g.getHeight() - (u8g.getFontAscent() + 4 - u8g.getFontDescent()) - 2;
    u8g.drawFrame(x, y, (u8g.getStrWidth("INICIO") + 4) + 2,
                  (u8g.getFontAscent() + 4 - u8g.getFontDescent()) + 2);
    u8g.drawStr((u8g.getWidth() - (u8g.getStrWidth("INICIO")) - 2),
                (u8g.getHeight() - 3), "INICIO");

  } while (u8g.nextPage());
  delay(3000);
  currentUI = UI_INICIO;
}
//</LCD DRAW>

#endif // UISPLASH_H