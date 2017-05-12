#ifndef RELOJ_H
#define RELOJ_H

#include <Time.h>
#include <TimeLib.h>
#include "Arduino.h"

char *anioStr() {
  char c[4];
  String(year()).toCharArray(c, 4);
  return c;
}

char *intToChar2(int dato) {
  char c[2];
  if (dato < 10) {
    c[0] = '0';
    c[1] = char(dato);
  } else {
    String(dato).toCharArray(c, 2);
  }
  return c;
}

char *mesStr() { return intToChar2(month()); }

char *diaStr() { return intToChar2(day()); }

char *horaStr() { return intToChar2(hour()); }

char *minutoStr() { return intToChar2(minute()); }

#endif // RELOJ_Hç