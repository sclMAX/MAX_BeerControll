#ifndef PANTALLA_H
#define PANTALLA_H

#include <U8glib.h>

U8GLIB_ST7920_128X64_1X u8g(LCD_PINS_D4, LCD_PINS_ENABLE,
                            LCD_PINS_RS); // SPI Com: (SCK, MOSI, CS)

#define OLLA_WIDTH 20
#define OLLA_HEIGTH 20
#ifndef LCD_PIXEL_WIDTH
#define LCD_PIXEL_WIDTH 128
#endif
#ifndef LCD_PIXEL_HEIGHT
#define LCD_PIXEL_HEIGHT 64
#endif
//  DRAW OLLA
inline void drawOlla(u8g_uint_t x, u8g_uint_t y, const int etiqueta, bool sel) {
  u8g_uint_t ollaAlto = OLLA_HEIGTH;
  u8g_uint_t ollaAncho = OLLA_WIDTH;
  u8g_uint_t ollaIntAncho = ollaAncho - 2;
  u8g_uint_t ollaIntAlto = ollaAlto - 1;
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
  u8g.setFont(u8g_font_chikita);
  if (sel) {
    u8g.setColorIndex(1); //  white on black
    u8g.drawBox(x + 4, y + 6, 12, 12);
    u8g.setColorIndex(0); //  white on black
  } else {
    u8g.setColorIndex(1); //  white on black
  }
  switch (etiqueta) {
  case 0:
    u8g.drawStr(x + 8, y + 14, "L");
    break;
  case 1:
    u8g.drawStr(x + 8, y + 14, "M");
    break;
  case 2:
    u8g.drawStr(x + 8, y + 14, "H");
    break;
  }

  u8g.setColorIndex(1); //  white on black
} // DRAW OLLA

void prueba(int item) {
  // picture loop
  u8g.firstPage();
  u8g_uint_t anchoPantalla = u8g.getWidth();
  do {

    // LICOR
    drawOlla(3, 8, 0, (item == 0));
    // MACERADOR
    drawOlla((anchoPantalla / 2) - (OLLA_WIDTH / 2), 8, 1, (item == 1));
    // HERVIDO
    drawOlla(anchoPantalla - (OLLA_WIDTH + 3), 8, 2, (item == 2));

  } while (u8g.nextPage());

  // rebuild the picture after some delay
  delay(1000);
}

#endif // PANTALLA_H