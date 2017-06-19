#include "bomba.h"
#include "Arduino.h"

Bomba::Bomba(int PIN) : pin(PIN)
{
    pinMode(pin, OUTPUT);
}

void Bomba::on()
{
    cli();
    digitalWrite(pin, HIGH);
    isOn = true;
    sei();
}

void Bomba::off()
{
    cli();
    digitalWrite(pin, LOW);
    isOn = false;
    sei();
}