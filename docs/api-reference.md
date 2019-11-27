# API reference

This page contains the API reference for Project OMEGA.

## Methods

- **void** init()

Sets the proper data transmission rate, and initializes the display and buttons. This function should be called first.

- **void** splash()

Accesses the display, drawing a bitmap of the omega symbol to it, before running the rest of your code.

- **int** poll()

Returns an integer from 4 to 8 inclusive if a button has just been pressed, or 0 if no button press is detected. The select button is associated with the lowest value of 4, followed by the right, up, left, and down buttons.

You should write your own function to determine how this should make your game behave, then call it repeatedly using `void update()`.

## Objects

- `matrix`

The display.

For a detailed description of the available graphics primitives, [read Adafruit's guide](https://learn.adafruit.com/adafruit-gfx-graphics-library/graphics-primitives).
