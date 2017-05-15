#ifndef UIDATA_H
#define UIDATA_H

#include "Arduino.h"
#include "beeperControl.h"
#include "config.h"
#include "imagenes.h"
#include <U8glib.h>
#include <stdlib.h>
//<LCD DRIVER>
//<FONTS>
#define FONT_TEMP_TARGET u8g_font_5x8
#define FONT_TEMP u8g_font_5x8         // u8g_font_chikita
#define FONT_ETIQUETA u8g_font_chikita // u8g_font_unifont
#define FONT_VERSION u8g_font_baby
#define FONT_FECHA u8g_font_chikita
#define FONT_HORA u8g_font_chikita
#define FONT_TITLE u8g_font_baby
#define FONT_CONFIG_ITEM u8g_font_chikita
//</FONTS>
#define TXT_ATRAS "<-"
U8GLIB_ST7920_128X64_1X u8g(LCD_PINS_D4, LCD_PINS_ENABLE,
                            LCD_PINS_RS); // SPI Com: (SCK, MOSI, CS)

u8g_uint_t LCDW = u8g.getWidth();
u8g_uint_t LCDH = u8g.getHeight();

void drawTitle(u8g_uint_t y, const char *txt) {
  u8g.setColorIndex(1);
  u8g.setFont(FONT_TITLE);
  u8g.setFontPosCenter();
  u8g_uint_t x = (LCDW / 2) - (u8g.getStrWidth(txt) / 2);
  u8g.setPrintPos(x, y + 4);
  u8g.print(txt);
  // u8g.drawRFrame(x - 3, y, u8g.getStrWidth(txt) + 6, 8, 2);
}
//</LCD DRIVER>

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

#define mSplashTam 6 // SPLASH: Dia Mes Año Hora Minuto Inicio
TMenuItem mSplash[mSplashTam];

#define mInicioTam 4 // SPLASH->INCIO:Licor  Macerador  Hervido Config
TMenuItem mInicio[mInicioTam];
//<MENU CONFIG>
#define mConfigTam 3 // SPLASH->INCIO->CONFIG: Atras Ollas SaveConfig
TMenuItem mConfig[mConfigTam];

#define mConfigOllasTam                                                        \
  4 // SPLASH->INCIO->CONFIG->OLLAS:Atras OllaLicor OllaMacerador OllaHervido
TMenuItem mConfigOllas[mConfigOllasTam];

#define mConfigOllasLicorTam                                                   \
  5 // SPLASH->INCIO->CONFIG->OLLAS->LICOR:Atras Temperatura HisteresisSup
    // HisteresisInf AjusteTemperatura
TMenuItem mConfigOllasLicor[mConfigOllasLicorTam];

#define mConfigOllasMaceradorTam                                               \
  5 // SPLASH->INCIO->CONFIG->OLLAS->MACERADOR:Atras Temperatura HisteresisSup
    // HisteresisInf AjusteTemperatura
TMenuItem mConfigOllasMacerador[mConfigOllasMaceradorTam];

#define mConfigOllasHervidoTam                                                 \
  5 // SPLASH->INCIO->CONFIG->OLLAS->HERVIDO:Atras Temperatura HisteresisSup
    // HisteresisInf AjusteTemperatura
TMenuItem mConfigOllasHervido[mConfigOllasHervidoTam];
//</MENU CONFIG>

//</MENUS>
//<ENCODER>
int16_t ecLast, ecValue, encoderValue;
int16_t selMenu = 0;
volatile bool isInSubMenu = false;
//</ENCODER>
//<PANTALLAS>
#define UI_SPLASH 0                 // SPLASH
#define UI_INICIO 1                 // SPLASH->INCIO
#define UI_CONFIG 2                 // SPLASH->INICIO->CONFIG
#define UI_CONFIG_OLLAS 3           // SPLASH->INICIO->CONFIG->OLLAS
#define UI_CONFIG_OLLAS_LICOR 4     // SPLASH->INICIO->CONFIG->OLLAS->LICOR
#define UI_CONFIG_OLLAS_MACERADOR 5 // SPLASH->INICIO->CONFIG->OLLAS->MACERADOR
#define UI_CONFIG_OLLAS_HERVIDO 6   // SPLASH->INICIO->CONFIG->OLLAS->HERVIDO

int16_t currentUI = UI_SPLASH; // DEFAULT SPLASH
//</PANTALLAS>

#endif // UIDATA_H