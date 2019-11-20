#include <Omega.h>

Omega omega = Omega();

int playerX = 2;
int playerY = 7;

const int mazeData[8][8] = {
  {1, 1, 1, 1, 0, 1, 1, 0},
  {0, 0, 0, 1, 0, 1, 0, 0},
  {0, 1, 0, 1, 0, 0, 0, 1},
  {0, 1, 1, 1, 0, 1, 1, 1},
  {0, 0, 0, 1, 0, 0, 0, 1},
  {0, 1, 0, 1, 0, 1, 1, 1},
  {0, 1, 0, 0, 0, 0, 0, 0},
  {0, 1, 0, 1, 0, 1, 1, 0},
};

void setup() {
  omega.init();
  omega.splash();

  omega.matrix.clear();
  viewCone();
}

void poll() {
  switch (omega.poll()) {
    case 0:
      break;
    case 5:
      if (playerX < 7 && mazeData[playerY][playerX + 1] == 0) {
        playerX = playerX + 1;
      }
      break;
    case 6:
      if (playerY > 0 && mazeData[playerY - 1][playerX] == 0) {
        playerY = playerY - 1;
      }
      break;
    case 7:
      if (playerX > 0 && mazeData[playerY][playerX - 1] == 0) {
        playerX = playerX - 1;
      }
      break;
    case 8:
      if (playerY < 7 && mazeData[playerY + 1][playerX] == 0) {
        playerY = playerY + 1;
      }
  }

  omega.matrix.clear();
  viewCone();
}

void viewCone() {
  if (mazeData[playerY - 1][playerX] == 1) {
    omega.matrix.drawPixel(playerX, playerY - 1, LED_ON);
  }
  if (mazeData[playerY][playerX - 1] == 1) {
    omega.matrix.drawPixel(playerX - 1, playerY, LED_ON);
  }
  if (mazeData[playerY][playerX + 1] == 1) {
    omega.matrix.drawPixel(playerX + 1, playerY, LED_ON);
  }

  omega.matrix.drawPixel(playerX, playerY, LED_ON);
  omega.matrix.writeDisplay();
}

/* void drawMaze() {
  omega.matrix.clear();
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (mazeData[j][i] == 1) {
        omega.matrix.drawPixel(i, j, LED_ON);
      }
    }
  }
  omega.matrix.writeDisplay();
} */

void loop() {
  poll();
}
