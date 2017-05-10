#ifndef PANTALLA_H
#define PANTALLA_H

#include "temperature.h"
#include "utils.h"
#include <U8glib.h>
#include <stdlib.h>
#include "imagenes.h"

U8GLIB_ST7920_128X64_1X u8g(LCD_PINS_D4, LCD_PINS_ENABLE,
                            LCD_PINS_RS); // SPI Com: (SCK, MOSI, CS)

#define P_SPLASH 0
#define P_INICIO 1

int16_t pantalla = P_SPLASH;

volatile int16_t encoderValue = 0, selMenu = -1, selSubMenu = -1;
volatile bool isSplashScreen = true;
#define FONT_TEMP_TARGET u8g_font_5x8
#define FONT_TEMP u8g_font_5x8         // u8g_font_chikita
#define FONT_ETIQUETA u8g_font_chikita // u8g_font_unifont
#define FONT_VERSION u8g_font_baby
#define FONT_FECHA u8g_font_chikita
#define OLLA_WIDTH 20
#define OLLA_HEIGTH 16

volatile bool isLicorSel = false;
volatile bool isMaceradorSel = false;
volatile bool isHervidoSel = false;

//  DRAW OLLA
void drawOlla(u8g_uint_t x, u8g_uint_t y, bool sel, Olla &olla) {
  u8g_uint_t ollaAlto = OLLA_HEIGTH;
  u8g_uint_t ollaAncho = OLLA_WIDTH;
  u8g_uint_t ollaIntAncho = ollaAncho - 2;
  u8g_uint_t ollaIntAlto = ollaAlto - 1;
  //*** OLLA ***
  u8g.drawBox(x, y, ollaAncho, ollaAlto);
  u8g.setColorIndex(0); //  white on black
  u8g.drawBox(x + 1, y, ollaIntAncho, ollaIntAlto);
  u8g.setColorIndex(1); // black on white
  bool updown = false;
  for (int i = x; i < (ollaAncho + x); i++) {
    int y1 = (updown) ? (y + 3) : (y + 4);
    updown = !updown;
    u8g.drawBox(i, y1, 1, 1);
  }
  //*** ETIQUETA ***
  u8g.setFont(FONT_ETIQUETA);
  if (sel && (selSubMenu == -1)) {
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
  //*** TARGET TEMPERATURA ***
  if ((selSubMenu != -1) && sel) {
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
  //*** TEMPERATURA ***
  u8g.setColorIndex(1);
  u8g.setFont(FONT_TEMP);
  u8g.setPrintPos(x + (ollaAncho / 2) -
                      (u8g.getStrWidth(itostr3left(olla.temperatura)) / 2),
                  y + ollaAlto + (u8g.getFontAscent() - u8g.getFontDescent()) +
                      6);
  u8g.print(itostr3left(olla.temperatura));
  //*** ESTADO QUEMADOR ***
  if (olla.isCalentar) {
    u8g.drawHLine(x, y + ollaAlto + 5, ollaAncho);
  }
  if (olla.isQuemadorOn) {
    for (int i = 0; i < ollaAncho; i += 4) {
      u8g.drawTriangle(x + i, y + ollaAlto + 4, x + i + 4, y + ollaAlto + 4,
                       x + i + 2, y + ollaAlto);
    }
  }

} // DRAW OLLA

// DRAW BOMBA
void drawBomba(u8g_uint_t x, u8g_uint_t y, bool sel) {
  u8g.setColorIndex(1);
  if ((sel) && (selSubMenu == -1)) {
    // u8g.drawCi
  }

} // DRAW BOMBA

// SPLASH SCREEN
void showSplash() {
  u8g.firstPage();
  do {
    u8g_uint_t logoHeight = 41;
    u8g.setFontPosTop();
    u8g.drawBitmapP(0, 0, LOGO_WIDTH, LOGO_HEIGHT, logo);
    u8g.setColorIndex(1);
    u8g.setFont(FONT_VERSION);
    u8g.drawStr((u8g.getWidth() - (u8g.getStrWidth(VERSION))), (logoHeight + 1),
                VERSION);
    u8g.setFont(FONT_FECHA);

  } while (u8g.nextPage());
} // SPLASH SCREEN

// INICIO
void showInicio() {
  u8g.firstPage();
  u8g_uint_t anchoPantalla = u8g.getWidth();
  u8g_uint_t licorX = 3;
  u8g_uint_t maceradorX = (anchoPantalla / 2) - (OLLA_WIDTH / 2);
  u8g_uint_t hervidoX = anchoPantalla - (OLLA_WIDTH + 3);
  u8g_uint_t todasY = 8;
  do {
    // LICOR
    drawOlla(licorX, todasY, isLicorSel, tempManager.Licor);
    // MACERADOR
    drawOlla(maceradorX, todasY, isMaceradorSel, tempManager.Macerador);
    // HERVIDO
    drawOlla(hervidoX, todasY, isHervidoSel, tempManager.Hervido);
  } while (u8g.nextPage());
} // INICIO

void updateLCD() {
  // picture loop
  switch (pantalla) {
  case P_SPLASH:
    showSplash();
    break;
  case P_INICIO:
    showInicio();
    break;
  }
  // rebuild the picture after some delay
  delay(300);
}

#endif // PANTALLA_H