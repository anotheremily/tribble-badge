/**
 * Button handling
 * Emily Young <emily@zavtralabs.com>
 *
 * Debounce code adapted from https://www.arduino.cc/en/tutorial/debounce
 */

#ifndef BUTTON_H
#define BUTTON_H

#include "Arduino.h"
#include "constants.h"

class Button {
public:
    Button(int);
    ~Button();

    int poll();
    bool isPressed();
private:
    int pin;
    int lastButtonState;
    int buttonState;
    int lastDebounceTime;
};

class ButtonManager {
public:
    ButtonManager();
    ~ButtonManager();

    int poll();
private:
    Button *buttonOne;
    Button *buttonTwo;
    int lastState;
};

#endif
