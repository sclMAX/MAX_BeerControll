#ifndef CONFIGSTORAGE_H
#define CONFIGSTORAGE_H

#include "Arduino.h"
#include <EEPROM.h>
#include "Reloj.h"
#include "temperature.h"
int version = 2;
int eeAdress = 0;

//<SAVE CONFIG>
void saveConfig() {
  Serial.println("**** INICIO GUARDADO CONFIG ****");
  eeAdress = 0;
  Serial.println("Guardando EEPROM Version...");
  EEPROM.put(eeAdress, version);
  eeAdress += sizeof(int);
  time_t f = now();
  Serial.println("Guardando Fecha y Hora actual...");
  EEPROM.put(eeAdress, f); // Fecha y hora
  eeAdress += sizeof(f);
  Serial.println("Guardando Config Olla Licor...");
  EEPROM.put(eeAdress, tempManager.Licor);
  eeAdress += sizeof(tempManager.Licor);
  Serial.println("Guardando Config Olla Macerador...");
  EEPROM.put(eeAdress, tempManager.Macerador);
  eeAdress += sizeof(tempManager.Macerador);
  Serial.println("Guardando Config Olla Hervido...");
  EEPROM.put(eeAdress, tempManager.Hervido);
  eeAdress += sizeof(tempManager.Hervido);
  Serial.println("**** FIN GUARDADO CONFIG ****");
} //</SAVE CONFIG>

void defaultConfig() {
  setTime(06, 30, 30, 13, 5, 2017); // setTime(hr,min,sec,day,month,yr);
  tempManager.Licor.etiqueta = 'L';
  tempManager.Macerador.etiqueta = 'M';
  tempManager.Hervido.etiqueta = 'H';
}

//<READ CONFIG>
void readConfig() {
  Serial.println("**** INICIO CARGA CONFIG ****");
  eeAdress = 0;
  int eeVersion = 0;
  Serial.println("Leyendo EEPROM Version...");
  EEPROM.get(eeAdress, eeVersion);
  if (eeVersion != version) {
    Serial.println("Version de EEPROM incompatible... Cargando default Config!");
    defaultConfig();
    return;
  }
  eeAdress += sizeof(int);
  time_t f;
  Serial.println("Leyendo Fecha y Hora...");
  EEPROM.get(eeAdress, f);
  setTime(f);
  eeAdress += sizeof(f);
  Serial.println("Leyendo Config Olla Licor...");
  EEPROM.get(eeAdress, tempManager.Licor);
  eeAdress += sizeof(tempManager.Licor);
  Serial.println("Leyendo Config Olla Macerador...");
  EEPROM.get(eeAdress, tempManager.Macerador);
  eeAdress += sizeof(tempManager.Macerador);
  Serial.println("Leyendo Config Olla Hervido...");
  EEPROM.get(eeAdress, tempManager.Hervido);
  eeAdress += sizeof(tempManager.Hervido);
  Serial.println("**** FIN CARGA CONFIG ****");
} //</READ CONFIG>

#endif // CONFIGSTORAGE_H
