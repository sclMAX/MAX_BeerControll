#ifndef UIDATA_H
#define UIDATA_H

#include "Arduino.h"
#include "config.h"
#include <stdlib.h>
#include <U8glib.h>


U8GLIB_ST7920_128X64_1X u8g(LCD_PINS_D4, LCD_PINS_ENABLE,
                            LCD_PINS_RS); // SPI Com: (SCK, MOSI, CS)

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

extern TMenuItem* currentMenu = 0;
int16_t encoderLast, encoderValue;
int16_t selMenu = -1, selSubMenu = -1;

#endif // UIDATA_H