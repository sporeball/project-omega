/*
  Omega.cpp
  collection of constant code for project OMEGA
  copyright (c) 2021 sporeball
  MIT license
*/

#include "Arduino.h"
#include "Wire.h"
#include <Bounce2.h>
#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpack.h>
#include <Omega.h>

const uint8_t PROGMEM splashData[8] = {
  B00000000,
  B00011000,
  B00100100,
  B01000010,
  B01000010,
  B00100100,
  B01100110,
  B00000000
};

Omega::Omega() {
  matrix = Adafruit_8x8matrix();
  _selectDebouncer = Bounce();
  _rightDebouncer = Bounce();
  _upDebouncer = Bounce();
  _leftDebouncer = Bounce();
  _downDebouncer = Bounce();
}

void Omega::init() {
  _selectDebouncer.attach(4, INPUT_PULLUP);
  _selectDebouncer.interval(50);
  _rightDebouncer.attach(5, INPUT_PULLUP);
  _rightDebouncer.interval(50);
  _upDebouncer.attach(6, INPUT_PULLUP);
  _upDebouncer.interval(50);
  _leftDebouncer.attach(7, INPUT_PULLUP);
  _leftDebouncer.interval(50);
  _downDebouncer.attach(8, INPUT_PULLUP);
  _downDebouncer.interval(50);

  Serial.begin(9600);
  matrix.begin(0x70);
}

void Omega::splash() {
  matrix.setBrightness(0);

  matrix.clear();
  matrix.drawRect(0, 0, 8, 8, LED_OFF);
  matrix.writeDisplay();
  delay(500);

  matrix.setBrightness(7);
  matrix.clear();
  matrix.drawBitmap(0, 0, splashData, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(1000);

  matrix.clear();
  matrix.drawRect(0, 0, 8, 8, LED_OFF);
  matrix.writeDisplay();
  delay(500);
}

int Omega::poll() {
  _selectDebouncer.update();
  _rightDebouncer.update();
  _upDebouncer.update();
  _leftDebouncer.update();
  _downDebouncer.update();

  if (_selectDebouncer.fell()) {
    return 4;
  } else if (_rightDebouncer.fell()) {
    return 5;
  } else if (_upDebouncer.fell()) {
    return 6;
  } else if (_leftDebouncer.fell()) {
    return 7;
  } else if (_downDebouncer.fell()) {
    return 8;
  } else {
    return 0;
  }
}
