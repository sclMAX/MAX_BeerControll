#ifndef MENUS_H
#define MENUS_H

#include "macros.h"
#include "pantalla.h"
#include "temperature.h"

#define MLICOR 0
#define MMACERADOR 1
#define MHERVIDO 2

typedef void (*screenFunc_t)();
typedef struct {
  screenFunc_t select;
  screenFunc_t click;
  screenFunc_t doubleClick;
  screenFunc_t held;
  screenFunc_t released;
  screenFunc_t pressed;
} TMenu;

typedef struct {
  TMenu menu;
  TMenu subMenu[4];
} TMenuItem;

volatile int16_t encoderValue, encoderInitValue = 0;

// LICOR MENU
void licorSelect() {
  isLicorSel = true;
  isMaceradorSel = isHervidoSel = false;
};
void licorClick() {
  if (!isSubMenuOlla) {
    tempManager.Licor.isCalentar = !tempManager.Licor.isCalentar;
  } else {
    isSubMenuOlla = false;
  }
  licorSelect();
};
void licorHeld() { isSubMenuOlla = true; };
void licorReleased() { encoderValue = (int)tempManager.Licor.tempTarget; }
// LICOR SUBMENU
void licorSubSelect() { tempManager.Licor.tempTarget = (float)encoderValue; };

// MACERADOR MENU
void maceradorSelect() {
  isMaceradorSel = true;
  isLicorSel = isHervidoSel = false;
};
void maceradorClick() {
  if (!isSubMenuOlla) {
    tempManager.Macerador.isCalentar = !tempManager.Macerador.isCalentar;
  } else {
    isSubMenuOlla = false;
  }
  maceradorSelect();
};
void maceradorHeld() { isSubMenuOlla = true; };
void maceradorReleased() {
  encoderValue = (int)tempManager.Macerador.tempTarget;
};
// MACERADOR SUBMENU
void maceradorSubSelect() {
  tempManager.Macerador.tempTarget = (float)encoderValue;
};

// HERVIDO MENU
void hervidoSelect() {
  isHervidoSel = true;
  isLicorSel = isMaceradorSel = false;
};
void hervidoClick() {
  if (!isSubMenuOlla) {
    tempManager.Hervido.isCalentar = !tempManager.Hervido.isCalentar;
  } else {
    isSubMenuOlla = false;
  }
  hervidoSelect();
};
void hervidoHeld() { isSubMenuOlla = true; };
void hervidoReleased() { encoderValue = (int)tempManager.Hervido.tempTarget; };
// HERVIDO SUBMENU
void hervidoSubSelect() {
  tempManager.Hervido.tempTarget = (float)encoderValue;
}

// INICIALIZACION DE MENUS
void initMenus(TMenuItem menu[]) {
  // LICOR MENU
  menu[MLICOR].menu.select = licorSelect;
  menu[MLICOR].menu.click = licorClick;
  menu[MLICOR].menu.held = licorHeld;
  menu[MLICOR].menu.released = licorReleased;
  // LICOR SUBMENU
  menu[MLICOR].subMenu[0].select = licorSubSelect;

  // MACERADOR MENU
  menu[MMACERADOR].menu.select = maceradorSelect;
  menu[MMACERADOR].menu.click = maceradorClick;
  menu[MMACERADOR].menu.held = maceradorHeld;
  menu[MMACERADOR].menu.released = maceradorReleased;
  // MACERADOR SUBMENU
  menu[MMACERADOR].subMenu[0].select = maceradorSubSelect;

  // HERVIDO MENU
  menu[MHERVIDO].menu.select = hervidoSelect;
  menu[MHERVIDO].menu.click = hervidoClick;
  menu[MHERVIDO].menu.held = hervidoHeld;
  menu[MHERVIDO].menu.released = hervidoReleased;
  // HERVIDO SUBMENU
  menu[MHERVIDO].subMenu[0].select = hervidoSubSelect;
}

#endif // MENUS_H