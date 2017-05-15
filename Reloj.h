#ifndef RELOJ_H
#define RELOJ_H

#include "Arduino.h"
#include <Time.h>
#include <TimeLib.h>
#include <TimeAlarms.h>

#define SEPARADOR_FECHA "/"
#define SEPARADOR_HORA ":"
char res[8];
#define DIGIT(n) ('0' + (n))
#define DIGIMOD(n) DIGIT((n) % 10)

char *anioStr() {
  int xx = year();
  res[0] = DIGIMOD(xx / 1000);
  res[1] = DIGIMOD(xx / 100);
  res[2] = DIGIMOD(xx / 10);
  res[3] = DIGIMOD(xx);
  res[4] = '\0';
  return res;
}

char *mesStr() {
  int xx = month();
  res[0] = DIGIMOD(xx / 10);
  res[1] = DIGIMOD(xx);
  res[2] = '\0';
  return res;
}

char *diaStr() {
  int xx = day();
  res[0] = DIGIMOD(xx / 10);
  res[1] = DIGIMOD(xx);
  res[2] = '\0';
  return res;
}

char *horaStr() {
  int xx = hour();
  res[0] = DIGIMOD(xx / 10);
  res[1] = DIGIMOD(xx);
  res[2] = '\0';
  return res;
}

char *minutoStr() {
  int xx = minute();
  res[0] = DIGIMOD(xx / 10);
  res[1] = DIGIMOD(xx);
  res[2] = '\0';
  return res;
}

#endif // RELOJ_Hç