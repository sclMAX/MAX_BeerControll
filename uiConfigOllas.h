#ifndef UICONFIGOLLAS_H
#define UICONFIGOLLAS_H

#include "Arduino.h"
#include "uidata.h"

//<MENU>
#ifndef imAtras
#define imAtras 0
#endif

//</MENU>
//<LCD>
void uiConfigOllasLCD() {
  u8g.firstPage();
  do {
    // TITULO
    drawTitle("Configuracion");
    drawItem(0, 16, imAtras, "Atras");
    drawItem(0, 24, imOllas, "Ollas");
  } while (u8g.nextPage());
}
//</LCD>
//<INIT>
void uiConfigOllasInit() {
  //<ATRAS>
  mConfig[imAtras].menu.click = imAtrasMenuClick;
  //</ATRAS>
  //<OLLAS>
  mConfig[imOllas].menu.click = imOllasMenuClick;
  //</OLLAS>
} //</INIT>

#endif // UICONFIGOLLAS_H