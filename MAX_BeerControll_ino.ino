#include "ClickEncoder.h"
#include "buzzer.h"
#include "config.h"
#include "pantalla.h"
#include "temperature.h"
#include <TimerOne.h>

Buzzer buzzer;

ClickEncoder *encoder;
int16_t last, value;
float tH, tL, tM;

void timerIsr() { encoder->service(); }

void setup() {

  Serial.begin(9600);
  encoder = new ClickEncoder(EN1, EN2, ENC, ENSTP);
  Timer1.initialize(1000);
  Timer1.attachInterrupt(timerIsr);
  last = -1;
  tH = -1;
  tM = -1;
  tL = -1;
  thermalManager.init();
}

void loop() {
  value -= encoder->getValue();
  thermalManager.updateTemp();
  if (tH != (int) thermalManager.getTempHervido()) {
    tH = (int) thermalManager.getTempHervido();
    Serial.print("Temp. Hervido:");
    Serial.println(tH);
  }
  if (tL != thermalManager.getTempLicor()) {
    tL =  thermalManager.getTempLicor();
    Serial.print("Temp. Licor:");
    Serial.println(tL);
  }
  if (tM != thermalManager.getTempMacerador()) {
    tM = thermalManager.getTempMacerador();
    Serial.print("Temp. Macerador:");
    Serial.println(tM);
  }

  if (value != last) {
    value = (value >= 0) ? value : 2;
    value = (value <= 2) ? value : 0;
    last = value;
    buzzer.tone(500, 5000);
    Serial.print("Encoder Value: ");
    Serial.println(value);
  }

  ClickEncoder::Button b = encoder->getButton();
  if (b != ClickEncoder::Open) {
    Serial.print("Button: ");
#define VERBOSECASE(label)                                                     \
  case label:                                                                  \
    Serial.println(#label);                                                    \
    buzzer.tone(2, 5000);                                                      \
    break;
    switch (b) {
      VERBOSECASE(ClickEncoder::Pressed)
      VERBOSECASE(ClickEncoder::Held)
      VERBOSECASE(ClickEncoder::Released)

    case ClickEncoder::Clicked:
      Serial.println("ClickEncoder::Clicked");
      buzzer.tone(2, 5000);
      break;
    case ClickEncoder::DoubleClicked:
      Serial.println("ClickEncoder::DoubleClicked");
      buzzer.tone(2, 5000);
      buzzer.tone(2, 5000);
      encoder->setAccelerationEnabled(!encoder->getAccelerationEnabled());
      Serial.print("  Acceleration is ");
      Serial.println((encoder->getAccelerationEnabled()) ? "enabled"
                                                         : "disabled");
      break;
    }
  }

  prueba(last);
}
