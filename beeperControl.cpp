#include "beeperControl.h"
#include "macros.h"
#include "fastio.h"
#include "config.h"
#include "Arduino.h"

static unsigned long Beeper::hz = 600;

Beeper::Beeper() { pinMode(BEEPER_PIN, OUTPUT); }
void Beeper::on() { tone(BEEPER_PIN, hz); };
void Beeper::off() { noTone(BEEPER_PIN); };
void Beeper::beep1(unsigned long duracion) { tone(BEEPER_PIN, hz, duracion); };
void Beeper::beep2(unsigned long duracion) {
  tone(BEEPER_PIN, hz, duracion);
  delay(duracion / 2);
  tone(BEEPER_PIN, hz, duracion);
};