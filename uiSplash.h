#ifndef UISPLASH_H
#define UISPLASH_H

#include "Arduino.h"
#include "Reloj.h"
#include "uidata.h"

//<MENU>
#define imDia 0
#define imMes 1
#define imAnio 2
#define imHora 3
#define imMinuto 4
#define imBtnInicio 5

//<COMUN>
void imSubMenuClick() {
  cli();
  isInSubMenu = false;
  ecValue = selMenu;
  sei();
};
void imMenuHeld() { isInSubMenu = true; };
//</COMUN>
//<DIA>
void imDiaSubMenuSelect() {
  cli();
  encoderValue = (ecValue >= 1) ? ((ecValue <= 31) ? ecValue : 1) : 31;
  ecValue = encoderValue;
  setTime(hour(), minute(), second(), (int)encoderValue, month(),
          year()); // setTime(hr,min,sec,day,month,yr);
  sei();
  
};
void imDiaMenuReleased() {
  cli();
  ecValue = day();
  sei();
};
//</DIA>
//<MES>
void imMesSubMenuSelect() {
  cli();
  encoderValue = (ecValue >= 1) ? ((ecValue <= 12) ? ecValue : 1) : 12;
  ecValue = encoderValue;
  setTime(hour(), minute(), second(), day(), (int)encoderValue,
          year()); // setTime(hr,min,sec,day,month,yr);
  sei();  
};
void imMesMenuReleased() {
  cli();
  ecValue = month();
  sei();
};
//</MES>
//<AÑO>
void imAnioSubMenuSelect() {
  cli();
  encoderValue = (ecValue >= 1970) ? ecValue : 1970;
  ecValue = encoderValue;
  setTime(hour(), minute(), second(), day(), month(),
          (int)encoderValue); // setTime(hr,min,sec,day,month,yr);
  sei();
  
};
void imAnioMenuReleased() {
  cli();
  ecValue = year();
  sei();
};
//</AÑO>
//<HORA>
void imHoraSubMenuSelect() {
  cli();
  encoderValue = (ecValue >= 0) ? ((ecValue <= 23) ? ecValue : 0) : 23;
  ecValue = encoderValue;
  setTime((int)encoderValue, minute(), second(), day(), month(),
          year()); // setTime(hr,min,sec,day,month,yr);
  sei();
};
void imHoraMenuReleased() {
  cli();
  ecValue = hour();
  sei();
};
//</HORA>
//<MINUTO>
void imMinutoSubMenuSelect() {
  cli();
  encoderValue = (ecValue >= 0) ? ((ecValue <= 59) ? ecValue : 0) : 59;
  ecValue = encoderValue;
  setTime(hour(), (int)encoderValue, second(), day(), month(),
          year()); // setTime(hr,min,sec,day,month,yr);
  sei();
};
void imMinutoMenuReleased() {
  cli();
  ecValue = minute();
  sei();
};
//</MINUTO>
//<BTNINICIO>
void imBtnInicioClick() {
  currentUI = UI_INICIO;
  uiInicioInit();
  selMenu = 0;
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
    if (isInSubMenu) {
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
    u8g_uint_t x = LCDW - (u8g.getStrWidth("INICIO") + 4) - 2;
    u8g_uint_t y = LCDH - (u8g.getFontAscent() + 4 - u8g.getFontDescent());
    if (selMenu == imBtnInicio) {
      u8g.drawRBox(x, y, (u8g.getStrWidth("INICIO") + 4) + 2,
                   (u8g.getFontAscent() + 4 - u8g.getFontDescent()), 3);
      u8g.setColorIndex(0);
    } else {
      u8g.drawRFrame(x, y, (u8g.getStrWidth("INICIO") + 4) + 2,
                     (u8g.getFontAscent() + 4 - u8g.getFontDescent()), 3);
    }
    u8g.drawStr((LCDW - (u8g.getStrWidth("INICIO")) - 2), (LCDH - 2), "INICIO");
    u8g.setColorIndex(1);

  } while (u8g.nextPage());
}
//</LCD DRAW>
//<INIT>
void uiSplashInit() {
  //<DIA>
  mSplash[imDia].menu.held = imMenuHeld;
  mSplash[imDia].menu.released = imDiaMenuReleased;
  mSplash[imDia].subMenu.select = imDiaSubMenuSelect;
  mSplash[imDia].subMenu.click = imSubMenuClick;

  //</DIA>
  //<MES>
  mSplash[imMes].menu.held = imMenuHeld;
  mSplash[imMes].menu.released = imMesMenuReleased;
  mSplash[imMes].subMenu.select = imMesSubMenuSelect;
  mSplash[imMes].subMenu.click = imSubMenuClick;
  //</MES>
  //<AÑO>
  mSplash[imAnio].menu.held = imMenuHeld;
  mSplash[imAnio].menu.released = imAnioMenuReleased;
  mSplash[imAnio].subMenu.select = imAnioSubMenuSelect;
  mSplash[imAnio].subMenu.click = imSubMenuClick;
  //</AÑO>
  //<HORA>
  mSplash[imHora].menu.held = imMenuHeld;
  mSplash[imHora].menu.released = imHoraMenuReleased;
  mSplash[imHora].subMenu.select = imHoraSubMenuSelect;
  mSplash[imHora].subMenu.click = imSubMenuClick;
  //</HORA>
  //<MINUTO>
  mSplash[imMinuto].menu.held = imMenuHeld;
  mSplash[imMinuto].menu.released = imMinutoMenuReleased;
  mSplash[imMinuto].subMenu.select = imMinutoSubMenuSelect;
  mSplash[imMinuto].subMenu.click = imSubMenuClick;
  //</MINUTO>
  //<BTNINICIO>
  mSplash[imBtnInicio].menu.click = imBtnInicioClick;
  //</BTNINICIO>
} //</INIT>

#endif // UISPLASH_H