/*
  Omega.h
  collection of constant code for project OMEGA
  copyright (c) 2021 sporeball
  MIT license
*/

#ifndef Omega_h
#define Omega_h

#include "Arduino.h"
#include "Wire.h"
#include <Bounce2.h>
#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpack.h>

class Omega {
  public:
    Omega();
    void init();
    void splash();
    int poll();
    Adafruit_8x8matrix matrix;
  private:
    Bounce _selectDebouncer;
    Bounce _rightDebouncer;
    Bounce _upDebouncer;
    Bounce _leftDebouncer;
    Bounce _downDebouncer;
};

#endif
