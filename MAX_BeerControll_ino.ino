#include "ClickEncoder.h"
#include <TimerOne.h>
extern unsigned long now = 0;
#include "config.h"
#include "pantalla.h"

ClickEncoder *encoder;
int16_t last, value;

void timerIsr() { encoder->service(); }

static void beeper(int retardo, int duracion) {
  delay(retardo);
  digitalWrite(BEEPER_PIN, HIGH);
  delay(duracion);
  digitalWrite(BEEPER_PIN, LOW);
}

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
    beeper(0, 10);
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
