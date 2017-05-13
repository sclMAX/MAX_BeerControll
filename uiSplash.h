#ifndef UISPLASH_H
#define UISPLASH_H

#include "Arduino.h"
#include "Reloj.h"
#include "uidata.h"

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
  Serial.println(encoderValue);
  selSubMenu = -1;
  encoderValue = selMenu;
  Serial.print("encoderValue = selMenu;");
  Serial.println(encoderValue);
};
void imMenuHeld() { selSubMenu = 0; };
//</COMUN>
//<DIA>
void imDiaSubMenuSelect() {
  encoderValue =
      (encoderValue >= 1) ? ((encoderValue <= 31) ? encoderValue : 1) : 31;
  Serial.println(encoderValue);
  setTime(hour(), minute(), second(), (int)encoderValue, month(),
          year()); // setTime(hr,min,sec,day,month,yr);
};
void imDiaMenuReleased() {
  Serial.print("imDiaMenuReleased()");
  Serial.println(encoderValue);
  encoderValue = day();
};
//</DIA>
//<MES>
void imMesSubMenuSelect() {
  Serial.println("imMesSubMenuSelect()");
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
void imBtnInicioClick() {
  currentUI = UI_INICIO;
  Serial.println("INICIO CALL");
}
//</BTNINICIO>
//</MENU>
//<LCD DRAW>
//<DRAW FECHA>
void insertSeparador(u8g_uint_t &x, u8g_uint_t &y, u8g_uint_t &m, char *s) {
  u8g_uint_t tw;
  u8g.setColorIndex(1);
  tw = u8g.getStrWidth(s);
  u8g.setPrintPos(x, y + m / 2);
  u8g.print(s);
  x = x + tw;
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
      u8g.drawBox(x, y, tw + m + 1, th + m);
      u8g.setColorIndex(0);
    } else {
      u8g.drawRFrame(x, y + 1, tw + m + 1, th + m, 1);
    }
  }
  u8g.setPrintPos(x + m, y + m / 2); // pos dentro del marco
  u8g.print(s);
  x = x + tw + m + 1;
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
  insertTime(x, y, m, imAnio, anioStr());     // Año
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
    if (selMenu == imBtnInicio) {
      u8g.drawRBox(x, y, (u8g.getStrWidth("INICIO") + 4) + 2,
                   (u8g.getFontAscent() + 4 - u8g.getFontDescent()) + 2, 3);
      u8g.setColorIndex(0);
    } else {
      u8g.drawRFrame(x, y, (u8g.getStrWidth("INICIO") + 4) + 2,
                     (u8g.getFontAscent() + 4 - u8g.getFontDescent()) + 2, 3);
    }
    u8g.drawStr((u8g.getWidth() - (u8g.getStrWidth("INICIO")) - 2),
                (u8g.getHeight() - 3), "INICIO");
    u8g.setColorIndex(1);

  } while (u8g.nextPage());
}
//</LCD DRAW>
//<INIT>
void uiSplashInit() {
  //<DIA>
  mSplash[imDia].menu.held = imMenuHeld;
  mSplash[imDia].menu.released = imDiaMenuReleased;
  mSplash[imDia].subMenu[0].select = imDiaSubMenuSelect;
  mSplash[imDia].subMenu[0].click = imSubMenuClick;

  //</DIA>
  //<MES>
  mSplash[imMes].subMenu[0].select = imMesSubMenuSelect;
  mSplash[imMes].subMenu[0].click = imSubMenuClick;
  mSplash[imMes].menu.held = imMenuHeld;
  mSplash[imMes].menu.released = imMesMenuReleased;
  //</MES>
  //<AÑO>
  mSplash[imAnio].subMenu[0].select = imAnioSubMenuSelect;
  mSplash[imAnio].subMenu[0].click = imSubMenuClick;
  mSplash[imAnio].menu.held = imMenuHeld;
  mSplash[imAnio].menu.released = imAnioMenuReleased;
  //</AÑO>
  //<HORA>
  mSplash[imHora].subMenu[0].select = imHoraSubMenuSelect;
  mSplash[imHora].subMenu[0].click = imSubMenuClick;
  mSplash[imHora].menu.held = imMenuHeld;
  mSplash[imHora].menu.released = imHoraMenuReleased;
  //</HORA>
  //<MINUTO>
  mSplash[imMinuto].subMenu[0].select = imMinutoSubMenuSelect;
  mSplash[imMinuto].subMenu[0].click = imSubMenuClick;
  mSplash[imMinuto].menu.held = imMenuHeld;
  mSplash[imMinuto].menu.released = imMinutoMenuReleased;
  //</MINUTO>
  //<BTNINICIO>
  mSplash[imBtnInicio].menu.click = imBtnInicioClick;
  //</BTNINICIO>
  selMenu = 0;
  selSubMenu = -1;
} //</INIT>

#endif // UISPLASH_H