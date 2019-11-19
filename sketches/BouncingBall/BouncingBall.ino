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

int ballX = 0;
int ballY = 2;
int xDirection = 1; // 1 is right, -1 is left
int yDirection = 1; // 1 is down, -1 is up

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
  matrix.drawPixel(ballX, ballY, LED_ON);
  matrix.writeDisplay();
  omegaReady = true;
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
  matrix.clear();
  matrix.drawPixel(ballX, ballY, LED_ON);
  matrix.drawLine(0, 7, 0, 1, LED_ON);
  matrix.drawLine(0, 0, 6, 0, LED_ON);
  matrix.drawLine(7, 0, 7, 7, LED_ON);
  matrix.writeDisplay();
  delay(200);
}

void loop() {
  if (omegaReady == true) {
    directionCheck();
    moveBall();
  }
}
