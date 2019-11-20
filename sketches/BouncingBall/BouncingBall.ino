#include <Omega.h>

Omega omega = Omega();

int ballX = 0;
int ballY = 2;
int xDirection = 1; // 1 is right, -1 is left
int yDirection = 1; // 1 is down, -1 is up

void setup() {
  omega.init();
  omega.splash();

  omega.matrix.clear();
  omega.matrix.drawPixel(ballX, ballY, LED_ON);
  omega.matrix.writeDisplay();
}

void directionCheck() {
  if (ballX == 1) {
    xDirection = 1;
  }
  if (ballX == 6) {
    xDirection = -1;
  }
  if (ballY == 1) {
    yDirection = 1;
  }
  if (ballY == 7) {
    yDirection = -1;
  }
}

void moveBall() {
  ballX = ballX + xDirection;
  ballY = ballY + yDirection;
  omega.matrix.clear();
  omega.matrix.drawPixel(ballX, ballY, LED_ON);
  omega.matrix.drawLine(0, 7, 0, 1, LED_ON);
  omega.matrix.drawLine(0, 0, 6, 0, LED_ON);
  omega.matrix.drawLine(7, 0, 7, 7, LED_ON);
  omega.matrix.writeDisplay();
  delay(200);
}

void loop() {
  directionCheck();
  moveBall();
}
