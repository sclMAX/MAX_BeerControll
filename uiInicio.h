#ifndef UIINICIO_H
#define UIINICIO_H

#include "Arduino.h"
#include "Reloj.h"
#include "temperature.h"
#include "uidata.h"
#include "utils.h"

//<MENU>
#define imLicor 0
#define imBombaRecirculado 1
#define imMacerador 2
#define imHervido 3
#define imConfig 4

//<COMUN>
int16_t chkEncoderValue(int16_t minimo, int16_t maximo) {
  cli();
  ecValue =
      (ecValue >= minimo) ? ((ecValue <= maximo) ? ecValue : maximo) : minimo;
  sei();
  return ecValue;
}
void MenuHeld() { isInSubMenu = true; };
void SubMenuClick() {
  cli();
  isInSubMenu = false;
  ecValue = selMenu;
  sei();
}
//</COMUN>

//<MENU LICOR>
void imLicorMenuClick() {
  tempManager.Licor.isCalentar = !tempManager.Licor.isCalentar;
};
void imLicorMenuReleased() {
  cli();
  ecValue = (int)tempManager.Licor.tempTarget;
  sei();
}
void imLicorSubMenuSelect() {
  tempManager.Licor.tempTarget =
      (float)chkEncoderValue(TEMP_TARGET_MIN, TEMP_TARGET_MAX);
};
//</MENU LICOR>
//<BOMBA R>
void imBombaRecirculadoMenuClick() {
  if (bombaR.isOn) {
    apagarBomba(bombaR);
  } else {
    prenderBombaR();
  }
}
//</BOMBA R
//<MACERADOR>
void imMaceradorMenuClick() {
  cli();
  tempManager.Macerador.isCalentar = !tempManager.Macerador.isCalentar;
  sei();
};
void imMaceradorMenuReleased() {
  cli();
  ecValue = (int)tempManager.Macerador.tempTarget;
  sei();
};
void imMaceradorSubMenuSelect() {
  tempManager.Macerador.tempTarget =
      (float)chkEncoderValue(TEMP_TARGET_MIN, TEMP_TARGET_MAX);
};
//</MACERADOR>
//<HERVIDO>
void imHervidoMenuClick() {
  cli();
  tempManager.Hervido.isCalentar = !tempManager.Hervido.isCalentar;
  sei();
};
void imHervidoMenuReleased() {
  cli();
  ecValue = (int)tempManager.Hervido.tempTarget;
  sei();
};
void imHervidoSubMenuSelect() {
  tempManager.Hervido.tempTarget =
      (float)chkEncoderValue(TEMP_TARGET_MIN, TEMP_TARGET_MAX);
}
//</HERVIDO>
//<CONFIG>
void imConfigMenuClick() {
  cli();
  currentUI = UI_CONFIG;
  selMenu = 0;
  sei();
}
//</CONFIG>

//</MENU>
//<LCD DRAW>

//<DRAW OLLA>
#define OLLA_WIDTH 20
#define OLLA_HEIGTH 16
volatile bool isA1 = false;
void uiInicioAnimationManager() {
  cli();
  isA1 = !isA1;
  sei();
}
void drawOlla(u8g_uint_t x, u8g_uint_t y, int sel, Olla &olla) {
  u8g_uint_t ollaAlto = OLLA_HEIGTH;
  u8g_uint_t ollaAncho = OLLA_WIDTH;
  u8g_uint_t ollaIntAncho = ollaAncho - 2;
  u8g_uint_t ollaIntAlto = ollaAlto - 1;
  //<OLLA>
  u8g.drawBox(x, y, ollaAncho, ollaAlto);
  u8g.setColorIndex(0); //  white on black
  u8g.drawBox(x + 1, y, ollaIntAncho, ollaIntAlto);
  u8g.setColorIndex(1); // black on white
  bool updown = false;
  for (int i = x; i < (ollaAncho + x); i++) {
    int y1 = (updown) ? (y + 3) : (y + 4);
    updown = !updown;
    u8g.drawBox(i, y1, 1, 1);
  } //</OLLA>
  //<ETIQUETA>
  u8g.setFont(FONT_ETIQUETA);
  if ((selMenu == sel) && (!isInSubMenu)) {
    u8g.setColorIndex(1); //  white on black
    u8g.drawBox((x + ((ollaAncho - ollaIntAncho) / 2) + 1), y + 6,
                (ollaIntAncho - 2), (ollaIntAlto - 7));
    u8g.setColorIndex(0); //  white on black
  } else {
    u8g.setColorIndex(1); //  white on black
  }
  u8g.setPrintPos((x + (ollaAncho / 2) -
                   ((u8g.getStrWidth(charToChar(olla.etiqueta)) / 2))),
                  y + 6 + ((ollaIntAlto - 7) / 2));
  u8g.setFontPosCenter();
  u8g.print(olla.etiqueta);
  //</ETIQUETA>
  //<TARGET TEMPERATURA>
  if ((isInSubMenu) && (selMenu == sel)) {
    u8g.setColorIndex(1);
    u8g.drawBox(x, 0, ollaAncho, 10);
    u8g.setColorIndex(0);
  } else {
    u8g.setColorIndex(1);
  }
  u8g.setFont(FONT_TEMP_TARGET);
  u8g.setPrintPos(x + (ollaAncho / 2) -
                      (u8g.getStrWidth(itostr3left(olla.tempTarget)) / 2),
                  y);
  u8g.print(itostr3left(olla.tempTarget));
  //</TARGET TEMPERATURA>
  //<TEMPERATURA>
  u8g.setColorIndex(1);
  u8g.setFont(FONT_TEMP);
  u8g.setPrintPos(x + (ollaAncho / 2) -
                      (u8g.getStrWidth(itostr3left(olla.temperatura)) / 2),
                  y + ollaAlto + (u8g.getFontAscent() - u8g.getFontDescent()) +
                      6);
  u8g.print(itostr3left(olla.temperatura));
  //</TEMPERATURA>
  //<ESTADO QUEMADOR>
  if (olla.isCalentar) {
    u8g.drawHLine(x, y + ollaAlto + 5, ollaAncho);
  }
  if (olla.isQuemadorOn) {
    for (int i = 0; i < ollaAncho; i += 4) {
      u8g.drawTriangle(x + i, y + ollaAlto + 4, x + i + 4, y + ollaAlto + 4,
                       x + i + 2, y + ollaAlto);
    }
  }
  //</ESTADO QUEMADOR>

} // </DRAW OLLA>

//<DRAW BOMBA>
void drawBomba(u8g_uint_t x, u8g_uint_t y, int sel, Bomba &b) {
  if (selMenu == sel) {
    u8g.setColorIndex(1);
    u8g.drawRBox(x + 5, y, 19, 16, 2);
    u8g.setColorIndex(0);
  } else {
    u8g.setColorIndex(1);
  }
  if (b.isOn) {
    if (isA1) {
      u8g.drawBitmapP(x, y, bomba_02_width, bomba_02_height, bomba_02_bits);
    } else {
      u8g.drawBitmapP(x, y, bomba_03_width, bomba_03_height, bomba_03_bits);
    }
  } else {
    u8g.drawBitmapP(x, y, bomba_01_width, bomba_01_height, bomba_01_bits);
    u8g.setColorIndex(1);
  }
  u8g.setColorIndex(1);
}

//</DRAW BOMBA>
//<HORA>
void drawHora(u8g_uint_t y) {
  u8g_uint_t x = 0;
  u8g.setColorIndex(1);
  u8g.setFont(FONT_HORA);
  u8g.setFontPosTop();
  x = LCDW - u8g.getStrWidth(minutoStr());
  u8g.setPrintPos(x, y);
  u8g.print(minutoStr());
  x = x - u8g.getStrWidth(":");
  u8g.setPrintPos(x, y);
  u8g.setColorIndex((isA1) ? 1 : 0);
  u8g.print(":");
  u8g.setColorIndex(1);
  x = x - u8g.getStrWidth(horaStr());
  u8g.setPrintPos(x, y);
  u8g.print(horaStr());
}
//</HORA>
//<BUTTON>
void drawBtnConfig() {
  if (selMenu == imConfig) {
    u8g.drawBitmapP(LCDW - 15, LCDH - 15, CONFIG_WIDTH, CONFIG_HEIGHT, config_02);
  } else {
    u8g.drawBitmapP(LCDW - 15, LCDH - 15, CONFIG_WIDTH, CONFIG_HEIGHT, config_01);
  }
}
//</BUTTON>
void uiInicioLCD() {
  u8g.firstPage();
  u8g_uint_t licorX = 3;
  u8g_uint_t maceradorX = (LCDW / 2) - (OLLA_WIDTH / 2);
  u8g_uint_t hervidoX = LCDW - (OLLA_WIDTH + 3);
  u8g_uint_t todasY = 8;
  do {
    // LICOR
    drawOlla(licorX, todasY, imLicor, tempManager.Licor);
    // BOMBA RECIRCULADO
    drawBomba(licorX + OLLA_WIDTH + 1, todasY, imBombaRecirculado, bombaR);
    // MACERADOR
    drawOlla(maceradorX, todasY, imMacerador, tempManager.Macerador);
    // HERVIDO
    drawOlla(hervidoX, todasY, imHervido, tempManager.Hervido);
    // HORA
    drawHora((todasY + OLLA_HEIGTH + 15));
    // BUTTONS
    drawBtnConfig();
  } while (u8g.nextPage());
}
//</LCD DRAW>
//<INIT>
void uiInicioInit() {
  //<LICOR>
  mInicio[imLicor].menu.click = imLicorMenuClick;
  mInicio[imLicor].menu.held = MenuHeld;
  mInicio[imLicor].menu.released = imLicorMenuReleased;
  mInicio[imLicor].subMenu.select = imLicorSubMenuSelect;
  mInicio[imLicor].subMenu.click = SubMenuClick;
  //</LICOR>
  //<BOMBA R>
  mInicio[imBombaRecirculado].menu.click = imBombaRecirculadoMenuClick;
  //</BOMBA R>
  //<MACERADOR>
  mInicio[imMacerador].menu.click = imMaceradorMenuClick;
  mInicio[imMacerador].menu.held = MenuHeld;
  mInicio[imMacerador].menu.released = imMaceradorMenuReleased;
  mInicio[imMacerador].subMenu.select = imMaceradorSubMenuSelect;
  mInicio[imMacerador].subMenu.click = SubMenuClick;
  //</MACERADOR>
  //<HERVIDO>
  mInicio[imHervido].menu.click = imHervidoMenuClick;
  mInicio[imHervido].menu.held = MenuHeld;
  mInicio[imHervido].menu.released = imHervidoMenuReleased;
  mInicio[imHervido].subMenu.select = imHervidoSubMenuSelect;
  mInicio[imHervido].subMenu.click = SubMenuClick;
  //</HERVIDO>
  //<CONFIG>
  mInicio[imConfig].menu.click = imConfigMenuClick;
  //</CONFIG>
  Alarm.timerRepeat(ANIMATION_DELAY, uiInicioAnimationManager);
} //</INIT>
#endif // UIINICIO_H