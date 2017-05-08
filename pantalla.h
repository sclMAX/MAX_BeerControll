#ifndef PANTALLA_H
#define PANTALLA_H

#include "temperature.h"
#include "utils.h"
#include <U8glib.h>
#include <stdlib.h>

U8GLIB_ST7920_128X64_1X u8g(LCD_PINS_D4, LCD_PINS_ENABLE,
                            LCD_PINS_RS); // SPI Com: (SCK, MOSI, CS)

#define FONT_5X8 u8g_font_5x8
#define FONT_5X5 u8g_font_chikita
#define OLLA_WIDTH 20
#define OLLA_HEIGTH 20

volatile bool isLicorSel = false;
volatile bool isMaceradorSel = false;
volatile bool isHervidoSel = false;
volatile bool isSubMenuOlla = false;

//  DRAW OLLA
inline void drawOlla(u8g_uint_t x, u8g_uint_t y, bool sel, Olla &olla) {
  u8g_uint_t ollaAlto = OLLA_HEIGTH;
  u8g_uint_t ollaAncho = OLLA_WIDTH;
  u8g_uint_t ollaIntAncho = ollaAncho - 2;
  u8g_uint_t ollaIntAlto = ollaAlto - 1;
  u8g_uint_t charH = 5;
  u8g_uint_t charW = 5;
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
  u8g.setFont(FONT_5X5);
  charW = 5;
  charH = 5;
  if (sel && !isSubMenuOlla) {
    u8g.setColorIndex(1); //  white on black
    u8g.drawBox((x + ((ollaAncho - ollaIntAncho) / 2) + 1), y + 7,
                (ollaIntAncho - 2), (ollaIntAlto - 8));
    u8g.setColorIndex(0); //  white on black
  } else {
    u8g.setColorIndex(1); //  white on black
  }
  //*** ETIQUETA ***
  u8g.setPrintPos((x + (ollaAncho / 2) - (charH / 2)), y + 15);
  u8g.print(olla.etiqueta);
  //*** TARGET TEMPERATURA ***
  if (isSubMenuOlla && sel) {
    u8g.setColorIndex(1);
    u8g.drawBox(x,0,ollaAncho,10);
    u8g.setColorIndex(0);
  }else{
    u8g.setColorIndex(1);
  }
  u8g.setFont(FONT_5X8);
  u8g.setPrintPos(x + (ollaAncho / 2) -
                      (u8g.getStrWidth(itostr3left(olla.tempTarget)) / 2),
                  y);
  u8g.print(itostr3left(olla.tempTarget));
  //*** TEMPERATURA ***
  u8g.setColorIndex(1);
  u8g.setFont(FONT_5X8);
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

void updateLCD() {
  // picture loop
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

  // rebuild the picture after some delay
   delay(100);
}

#endif // PANTALLA_H