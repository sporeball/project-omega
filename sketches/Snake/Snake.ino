#include <Omega.h>

Omega omega = Omega();

int playerX = 1;
int playerY = 1;
int xVel = 1;
int yVel = 0;

unsigned long prevMillis = 0;
const int moveInterval = 300;

void setup() {
  omega.init();
  omega.splash();

  omega.matrix.clear();
  omega.matrix.drawPixel(1, 1, LED_ON);
  omega.matrix.writeDisplay();
}

void poll() {
  switch (omega.poll()) {
    case 0:
      break;
    case 4:
      break;
    case 5:
      xVel = 1;
      yVel = 0;
      break;
    case 6:
      xVel = 0;
      yVel = -1;
      break;
    case 7:
      xVel = -1;
      yVel = 0;
      break;
    case 8:
      xVel = 0;
      yVel = 1;
  }
}

void moveSnake() {
  playerX = playerX + xVel;
  if (playerX < 0) {
    playerX = 0;
  }
  if (playerX > 7) {
    playerX = 7;
  }
  
  playerY = playerY + yVel;
  if (playerY < 0) {
    playerY = 0;
  }
  if (playerY > 7) {
    playerY = 7;
  }
}

void redraw() {
  omega.matrix.clear();
  omega.matrix.drawPixel(playerX, playerY, LED_ON);
  omega.matrix.writeDisplay();
}

void loop() {
  unsigned long currMillis = millis();
  if (currMillis - prevMillis >= moveInterval) {
    prevMillis = currMillis;
    moveSnake();
  }
  
  poll();
  redraw();
}
