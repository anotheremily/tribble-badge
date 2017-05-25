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
    Button(uint8_t);
    ~Button();

    uint8_t poll();
    bool isPressed();
private:
    uint8_t pin;
    uint8_t lastButtonState;
    uint8_t buttonState;
    uint16_t lastDebounceTime;
};

class ButtonManager {
public:
    ButtonManager();
    ~ButtonManager();

    uint8_t poll();
private:
    Button *buttonOne;
    Button *buttonTwo;
    uint8_t lastState;
};

#endif
