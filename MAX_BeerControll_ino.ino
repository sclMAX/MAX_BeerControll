#include "ClickEncoder.h"
#include <TimerOne.h>
#include "config.h"
#include "pantalla.h"
#include "buzzer.h"

ClickEncoder *encoder;
int16_t last, value;

void timerIsr() { encoder->service(); }

void setup() {

  Serial.begin(9600);
  encoder = new ClickEncoder(EN1, EN2, ENC, ENSTP);
  pinMode(BEEPER_PIN, OUTPUT);
  Timer1.initialize(1000);
  Timer1.attachInterrupt(timerIsr);
  last = -1;
}

void loop() {
  value -= encoder->getValue();

  if (value != last) {
    value = (value >= 0) ? value : 2;
    value = (value <= 2) ? value : 0;
    last = value;
    buzzer.tone(2, 5000);
    Serial.print("Encoder Value: ");
    Serial.println(value);
  }

  ClickEncoder::Button b = encoder->getButton();
  if (b != ClickEncoder::Open) {
    Serial.print("Button: ");
#define VERBOSECASE(label)                                                     \
  case label:                                                                  \
    Serial.println(#label);                                                    \
    beeper(0, 20);                                                             \
    break;
    switch (b) {
      VERBOSECASE(ClickEncoder::Pressed)
      VERBOSECASE(ClickEncoder::Held)
      VERBOSECASE(ClickEncoder::Released)

    case ClickEncoder::Clicked:
      Serial.println("ClickEncoder::Clicked");
      beeper(0, 10);
      break;
    case ClickEncoder::DoubleClicked:
      Serial.println("ClickEncoder::DoubleClicked");
      beeper(0, 10);
      beeper(20, 10);
      encoder->setAccelerationEnabled(!encoder->getAccelerationEnabled());
      Serial.print("  Acceleration is ");
      Serial.println((encoder->getAccelerationEnabled()) ? "enabled"
                                                         : "disabled");
      break;
    }
  }

  prueba(last);
}

