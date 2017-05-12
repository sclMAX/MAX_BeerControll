#ifndef UIDATA_H
#define UIDATA_H

#include "Arduino.h"
#include "config.h"
#include "beeperControl.h"
#include "imagenes.h"
#include <stdlib.h>
#include <U8glib.h>

U8GLIB_ST7920_128X64_1X u8g(LCD_PINS_D4, LCD_PINS_ENABLE,
                            LCD_PINS_RS); // SPI Com: (SCK, MOSI, CS)

u8g_uint_t LCDW = u8g.getWidth();
u8g_uint_t LCDH = u8g.getHeight();

//<FONTS>
#define FONT_TEMP_TARGET u8g_font_5x8
#define FONT_TEMP u8g_font_5x8         // u8g_font_chikita
#define FONT_ETIQUETA u8g_font_chikita // u8g_font_unifont
#define FONT_VERSION u8g_font_baby
#define FONT_FECHA u8g_font_chikita
//</FONTS>


typedef void (*screenFunc_t)();
typedef struct {
  screenFunc_t select;
  screenFunc_t click;
  screenFunc_t doubleClick;
  screenFunc_t held;
  screenFunc_t released;
} TMenu;

typedef struct {
  TMenu menu;
  TMenu subMenu[];
} TMenuItem;

extern TMenuItem *currentMenu = 0;
int16_t encoderLast = -1, encoderValue = 0;
int16_t selMenu = -1, selSubMenu = -1;

#define UI_SPLASH 0
#define UI_INICIO 1

int16_t currentUI = UI_SPLASH;

#endif // UIDATA_H