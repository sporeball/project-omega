#include <Omega.h>

Omega omega = Omega();

void setup() {
  omega.init();
  omega.splash();
}

void loop() {
  tone(11, 440, 500);
  delay(500);
  noTone(11);
  delay(500);
}
