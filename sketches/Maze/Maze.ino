#include <Bounce2.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

Adafruit_8x8matrix matrix = Adafruit_8x8matrix();
bool omegaReady = false; // is the splash done?

#define SELECT_BUTTON 4
#define RIGHT_BUTTON 5
#define UP_BUTTON 6
#define LEFT_BUTTON 7
#define DOWN_BUTTON 8

Bounce selectButtonDebouncer = Bounce();
Bounce rightButtonDebouncer = Bounce();
Bounce upButtonDebouncer = Bounce();
Bounce leftButtonDebouncer = Bounce();
Bounce downButtonDebouncer = Bounce();

static const uint8_t PROGMEM omega_bmp[] = {
  B00000000,
  B00011000,
  B00100100,
  B01000010,
  B01000010,
  B00100100,
  B01100110,
  B00000000
};

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

int playerX = 2;
int playerY = 7;

void setup() {
  selectButtonDebouncer.attach(SELECT_BUTTON, INPUT_PULLUP);
  selectButtonDebouncer.interval(25);
  rightButtonDebouncer.attach(RIGHT_BUTTON, INPUT_PULLUP);
  rightButtonDebouncer.interval(25);
  upButtonDebouncer.attach(UP_BUTTON, INPUT_PULLUP);
  upButtonDebouncer.interval(25);
  leftButtonDebouncer.attach(LEFT_BUTTON, INPUT_PULLUP);
  leftButtonDebouncer.interval(25);
  downButtonDebouncer.attach(DOWN_BUTTON, INPUT_PULLUP);
  downButtonDebouncer.interval(25);
  
  Serial.begin(9600);
  matrix.begin(0x70);
  
  matrix.setBrightness(7);

  matrix.clear();
  matrix.drawRect(0, 0, 8, 8, LED_OFF);
  delay(1000);

  // draw the splash
  matrix.clear();
  matrix.drawBitmap(0, 0, omega_bmp, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(1000);

  // clear the splash
  matrix.clear();
  matrix.drawRect(0, 0, 8, 8, LED_OFF);
  matrix.writeDisplay();
  delay(500);

  // initialize view cone
  viewCone();
  omegaReady = true;
}

void buttonPress(int pin) {
  switch (pin) {
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
      break;
  }

  matrix.clear();
  viewCone();
}

void viewCone() {
  if (mazeData[playerY - 1][playerX] == 1) {
    matrix.drawPixel(playerX, playerY - 1, LED_ON);
  }
  if (mazeData[playerY][playerX - 1] == 1) {
    matrix.drawPixel(playerX - 1, playerY, LED_ON);
  }
  if (mazeData[playerY][playerX + 1] == 1) {
    matrix.drawPixel(playerX + 1, playerY, LED_ON);
  }

  matrix.drawPixel(playerX, playerY, LED_ON);
  matrix.writeDisplay();
}

void drawMaze() {
  matrix.clear();
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (mazeData[j][i] == 1) {
        matrix.drawPixel(i, j, LED_ON);
      }
    }
  }
  matrix.writeDisplay();
}

void loop() {
  if (omegaReady == true) {
    selectButtonDebouncer.update();
    rightButtonDebouncer.update();
    upButtonDebouncer.update();
    leftButtonDebouncer.update();
    downButtonDebouncer.update();
    if (selectButtonDebouncer.fell()) {
      drawMaze();
    }
    if (rightButtonDebouncer.fell()) {
      buttonPress(5);
    }
    if (upButtonDebouncer.fell()) {
      buttonPress(6);
    }
    if (leftButtonDebouncer.fell()) {
      buttonPress(7);
    }
    if (downButtonDebouncer.fell()) {
      buttonPress(8);
    }
  }
}
