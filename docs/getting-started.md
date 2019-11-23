# Getting started

This tutorial will act as a step-by-step guide to get you writing and running your first Project OMEGA game.

## Setup

Make sure you've installed the Arduino IDE for your operating system of choice before continuing. From there, you'll need to install Project OMEGA's dependencies:

- [Adafruit_GFX](https://github.com/adafruit/Adafruit-GFX-Library)
- [Adafruit_LEDBackpack](https://github.com/adafruit/Adafruit_LED_Backpack)
- [Bounce2](https://github.com/thomasfredericks/Bounce2)

!!! caution
    The version of the Bounce2 library that's hosted at the provided GitHub link **will not work** with Project OMEGA. Be sure to install it through the Arduino IDE, in Tools > Manage Libraries.

After everything is installed, open up a blank sketch in the Arduino IDE. You should see the standard `setup()` and `loop()` functions. Don't worry about these for now; we'll get to them in a moment.

## Importing the library

To import the Project OMEGA library, add the following lines just before the `setup()` function:

```
#include <Omega.h>
Omega omega = Omega();
```

The first line actually imports the definitions added by the library; the second line creates an object named `omega` with the same definitions. You'll use this object in your game code later on.

!!! note
    `omega` is the recommended name for the object, though you can change it to any other name you'd like.

## The setup function

The `setup()` function will run just once, at the beginning of your sketch's execution.

Add the line `omega.init();` inside it. This is used to set up the board's buttons and display; as such, your program will not run without it.

If you'd like, you can call the `splash()` function after this, using `omega.splash();`. This is completely optional, though recommended. With this change, a bitmap of the Greek letter omega will be drawn to the display before your game code starts to execute.

Finally, we should try drawing something to the display. Add the following lines of code to the end of the function:

```
omega.matrix.clear();
omega.matrix.drawPixel(0, 0, LED_ON);
omega.matrix.writeDisplay();
```

This will use methods added by Adafruit's graphics library to clear the display and light up the pixel in the top left corner.

## The loop function

To make proper use of the `loop()` function, we'll have to use one more OMEGA-defined method: `omega.poll()`. This will repeatedly return an integer from 4 to 8 back to your code if a button was pressed, and 0 otherwise. You'll need to write your own function to determine how this should make your game behave.

Add the following function definition to your Arduino sketch, before `void loop()`:

```
void poll() {
  switch (omega.poll()) {
    case 0:
      break;
    default:
      omega.matrix.drawPixel(0, 0, LED_OFF);
      omega.matrix.writeDisplay();
      delay(125);
  }

  omega.matrix.clear();
  omega.matrix.drawPixel(0, 0, LED_ON);
  omega.matrix.writeDisplay();
}
```

This function is actually pretty simple! The `switch` keyword says to do something depending on the output of what's in the parentheses &mdash; in this case, a call to `omega.poll()`. We do nothing if it returns a 0, and every other case will do the same thing: turn off the pixel in the top left corner of the display. Outside of the `switch` block, we then turn it on again after a fraction of a second.

Finally, we change the `loop()` function so that it repeatedly calls our new `poll()` function:

```
void loop() {
  poll();
}
```

If you set everything up correctly, you should be able to make the top left pixel of the display flash any time you press a button!

!!! note
    When writing your `poll()` function, you'll typically want to add a new case for each of the buttons you plan to detect. Remember that these are connected to the numbers 4 through 8, not 0.

## The final result

```
#include <Omega.h>
Omega omega = Omega();

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
    default:
      omega.matrix.drawPixel(0, 0, LED_OFF);
      omega.matrix.writeDisplay();
      delay(125);
  }

  omega.matrix.clear();
  omega.matrix.drawPixel(0, 0, LED_ON);
  omega.matrix.writeDisplay();
}

void loop() {
  poll();
}
```

Congratulations! You've just written your first Project OMEGA game.
