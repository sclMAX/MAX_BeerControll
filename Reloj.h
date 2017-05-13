#ifndef RELOJ_H
#define RELOJ_H

#include "Arduino.h"
#include <Time.h>
#include <TimeLib.h>

#define SEPARADOR_FECHA "/"
#define SEPARADOR_HORA ":"
char conv[8];
#define DIGIT(n) ('0' + (n))
#define DIGIMOD(n) DIGIT((n) % 10)

char *anioStr() {
  int xx = year();
  conv[0] = DIGIMOD(xx / 1000);
  conv[1] = DIGIMOD(xx / 100);
  conv[2] = DIGIMOD(xx / 10);
  conv[3] = DIGIMOD(xx);
  conv[4] = '\0';
  return conv;
}

char *mesStr() {
  int xx = month();
  conv[0] = DIGIMOD(xx / 10);
  conv[1] = DIGIMOD(xx);
  conv[2] = '\0';
  return conv;
}

char *diaStr() {
  int xx = day();
  conv[0] = DIGIMOD(xx / 10);
  conv[1] = DIGIMOD(xx);
  conv[2] = '\0';
  return conv;
}

char *horaStr() {
  int xx = hour();
  conv[0] = DIGIMOD(xx / 10);
  conv[1] = DIGIMOD(xx);
  conv[2] = '\0';
  return conv;
}

char *minutoStr() {
  int xx = minute();
  conv[0] = DIGIMOD(xx / 10);
  conv[1] = DIGIMOD(xx);
  conv[2] = '\0';
  return conv;
}

#endif // RELOJ_Hç