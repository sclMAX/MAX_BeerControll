#ifndef UIDATA_H
#define UIDATA_H

#include "Arduino.h"
#include "beeperControl.h"
#include "config.h"
#include "imagenes.h"
#include <U8glib.h>
#include <stdlib.h>
//<LCD DRIVER>
U8GLIB_ST7920_128X64_1X u8g(LCD_PINS_D4, LCD_PINS_ENABLE,
                            LCD_PINS_RS); // SPI Com: (SCK, MOSI, CS)

u8g_uint_t LCDW = u8g.getWidth();
u8g_uint_t LCDH = u8g.getHeight();
//</LCD DRIVER>

//<FONTS>
#define FONT_TEMP_TARGET u8g_font_5x8
#define FONT_TEMP u8g_font_5x8         // u8g_font_chikita
#define FONT_ETIQUETA u8g_font_chikita // u8g_font_unifont
#define FONT_VERSION u8g_font_baby
#define FONT_FECHA u8g_font_chikita
#define FONT_HORA u8g_font_chikita
//</FONTS>
//<MENUS>
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
  TMenu subMenu;
} TMenuItem;

#define mSplashTam 6 // Dia Mes Año Hora Minuto Inicio
TMenuItem mSplash[mSplashTam];

#define mInicioTam 4  // Licor  Macerador  Hervido Config
TMenuItem mInicio[mInicioTam];

//</MENUS>
//<ENCODER>
int16_t ecLast, ecValue, encoderValue;
int16_t selMenu = 0;
volatile bool isInSubMenu = false;
//</ENCODER>
//<PANTALLAS>
#define UI_SPLASH 0
#define UI_INICIO 1

int16_t currentUI = UI_SPLASH;
//</PANTALLAS>

#endif // UIDATA_H