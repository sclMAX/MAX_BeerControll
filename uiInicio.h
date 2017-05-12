#ifndef UIINICIO_H
#define UIINICIO_H

#include "uidata.h"
#include "Reloj.h"
#include "macros.h"
#include "Arduino.h"

TMenuItem uiInicioMenu[6];

#define imDia 0
#define imMes 1
#define imAnio 2
#define imHora 3
#define imMinuto 4
#define imBtnInicio 5
//<DIA>
void imDiaSubMenuSelect() {
  encoderValue =
      (encoderValue >= 1) ? ((encoderValue <= 31) ? encoderValue : 1) : 31;
  setTime(hour(), minute(), second(), encoderValue, month(),
          year()); // setTime(hr,min,sec,day,month,yr);
};
void imDiaSubMenuClick() { selSubMenu = -1; };
void imDiaMenuHeld() { selSubMenu = 0; };
void imDiaMenuReleased() { encoderValue = day(); };
//</DIA>

void uiInicioInit() { //<INIT>
  uiInicioMenu[imDia].subMenu[0].select = imDiaSubMenuSelect;
  uiInicioMenu[imDia].subMenu[0].click = imDiaSubMenuClick;
  uiInicioMenu[imDia].menu.held = imDiaMenuHeld;
  uiInicioMenu[imDia].menu.released = imDiaMenuReleased;

  if (currentMenu != 0) {
    delete[] currentMenu;
  }
  currentMenu = new TMenuItem[COUNT(uiInicioMenu)];
  for (int i = 0; i < COUNT(uiInicioMenu); i++) {
    currentMenu[i] = uiInicioMenu[i];
  }
  selMenu = 0;
  selSubMenu = -1;
} //</INIT>

#endif // UIINICIO_H