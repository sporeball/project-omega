#include <Omega.h>

Omega omega = Omega();

int playerX = 0;
int playerY = 0;

void setup() {
  omega.init();
  omega.splash();

  omega.matrix.clear();
  omega.matrix.drawPixel(0, 0, LED_ON);
  omega.matrix.writeDisplay();
}

void poll() {
  switch (omega.poll()) {
    case 0:
      break;
    case 4:
      omega.matrix.drawPixel(playerX, playerY, LED_OFF);
      omega.matrix.writeDisplay();
      delay(125);
      break;
    case 5:
      if (playerX < 7) {
        playerX = playerX + 1;
      } else {
        playerX = 0;
      }
      break;
    case 6:
      if (playerY > 0) {
        playerY = playerY - 1;
      } else {
        playerY = 7;
      }
      break;
    case 7:
      if (playerX > 0) {
        playerX = playerX - 1;
      } else {
        playerX = 7;
      }
      break;
    case 8:
      if (playerY < 7) {
        playerY = playerY + 1;
      } else {
        playerY = 0;
      }
  }
  
  omega.matrix.clear();
  omega.matrix.drawPixel(playerX, playerY, LED_ON);
  omega.matrix.writeDisplay();
}

void loop() {
  poll();
}
