#include "ClickEncoder.h"
#include "buzzer.h"
#include "config.h"
#include "pantalla.h"
#include "temperature.h"
#include <TimerOne.h>
#include "menus.h"

ClickEncoder *encoder;
// Temperature *tempManager;
Buzzer buzzer;

int16_t last, value;

void timerIsr() { encoder->service(); }

void manageEncoder() {
  value -= encoder->getValue();
  if (value != last) {
    value = (value >= 0) ? value : 2;
    value = (value <= 2) ? value : 0;
    last = value;
    //   buzzer.tone(500, 5000);
    Serial.print("Encoder Value: ");
    Serial.println(value);
  }

  ClickEncoder::Button b = encoder->getButton();
  if (b != ClickEncoder::Open) {
#define VERBOSECASE(label)                                                     \
  case label:                                                                  \
    Serial.println(#label);                                                    \
    break;
    switch (b) {
      VERBOSECASE(ClickEncoder::Pressed)
      VERBOSECASE(ClickEncoder::Held)
      VERBOSECASE(ClickEncoder::Released)
    case ClickEncoder::Clicked:
      Serial.println("ClickEncoder::Clicked");
      switch (value){
        case 0 :
          tempManager.Licor.isCalentar = !tempManager.Licor.isCalentar;
          break;
        case 1 :
          tempManager.Macerador.isCalentar = !tempManager.Macerador.isCalentar;
          break;
        case 2 :
          tempManager.Hervido.isCalentar = !tempManager.Hervido.isCalentar;
          break;
      }
      break;
    case ClickEncoder::DoubleClicked:
      Serial.println("ClickEncoder::DoubleClicked");
      //   buzzer.tone(2, 5000);
      //   buzzer.tone(2, 5000);
      encoder->setAccelerationEnabled(!encoder->getAccelerationEnabled());
      Serial.print("  Acceleration is ");
      Serial.println((encoder->getAccelerationEnabled()) ? "enabled"
                                                         : "disabled");
      break;
    }
  }
}

void setup() {

  Serial.begin(9600);
  encoder = new ClickEncoder(EN1, EN2, ENC, ENSTP);
  Timer1.initialize(1000);
  Timer1.attachInterrupt(timerIsr);
  last = -1;
  tempManager.init();
  tempManager.Licor.etiqueta = 'L';
  tempManager.Macerador.etiqueta = 'M';
  tempManager.Hervido.etiqueta = 'H';
  tempManager.Licor.tempTarget = 80;
  tempManager.Macerador.tempTarget = 67;
  tempManager.Hervido.tempTarget = 23;
}

void loop() {
  manageEncoder();
  tempManager.manageTemp();
  prueba(last);
}
