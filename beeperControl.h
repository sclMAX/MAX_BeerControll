#ifndef BEEPERCONTROL_H
#define BEEPERCONTROL_H

class Beeper {
public:
  Beeper();
  void on();
  void off();
  void beep1(unsigned long);
  void beep2(unsigned long);
  static unsigned long hz;
};

extern Beeper beeper;
#endif // BEEPERCONTROL_H