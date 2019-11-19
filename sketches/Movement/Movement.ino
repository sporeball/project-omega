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

int playerX = 0;
int playerY = 0;

void setup() {
  selectButtonDebouncer.attach(SELECT_BUTTON, INPUT_PULLUP);
  selectButtonDebouncer.interval(50);
  rightButtonDebouncer.attach(RIGHT_BUTTON, INPUT_PULLUP);
  rightButtonDebouncer.interval(50);
  upButtonDebouncer.attach(UP_BUTTON, INPUT_PULLUP);
  upButtonDebouncer.interval(50);
  leftButtonDebouncer.attach(LEFT_BUTTON, INPUT_PULLUP);
  leftButtonDebouncer.interval(50);
  downButtonDebouncer.attach(DOWN_BUTTON, INPUT_PULLUP);
  downButtonDebouncer.interval(50);
  
  Serial.begin(9600);
  matrix.begin(0x70);
  
  matrix.setBrightness(1);

  matrix.clear();
  matrix.drawRect(0, 0, 8, 8, LED_OFF);
  matrix.writeDisplay();
  delay(500);

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

  // initial pixel
  matrix.clear();
  matrix.drawPixel(0, 0, LED_ON);
  matrix.writeDisplay();
  omegaReady = true;
}

void buttonPress(int pin) {
  switch (pin) {
    case 4:
      matrix.drawPixel(playerX, playerY, LED_OFF);
      matrix.writeDisplay();
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
      break;
  }
  // Serial.println(playerX);
  matrix.clear();
  matrix.drawPixel(playerX, playerY, LED_ON);
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
      buttonPress(4);
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
