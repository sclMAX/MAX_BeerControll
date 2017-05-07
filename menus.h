#ifndef MENUS_H
#define MENUS_H

#include "macros.h"

#define MLICOR 0 

typedef void (*screenFunc_t)();
typedef struct {
    screenFunc_t select;
    screenFunc_t click;
    screenFunc_t doubleClick;
    screenFunc_t held;
    screenFunc_t released;
    screenFunc_t pressed;
}TMenu;

typedef struct {
    TMenu menu;
    TMenu subMenu;
} TMenuItem;

extern TMenuItem menu [3];

void initMenu() {
    menu[MLICOR].menu 
}


#endif // MENUS_H