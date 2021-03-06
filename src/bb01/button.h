/**
 * Button handling
 * Emily Young <emily@zavtralabs.com>
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
    bool maybePressed();
private:
    uint8_t pin;
    uint8_t prevState[2];
    uint8_t buttonState;
    // uint16_t lastDebounceTime;
};

class ButtonHandler {
public:
    ButtonHandler();
    ~ButtonHandler();

    uint8_t poll();
private:
    Button *buttonOne;
    Button *buttonTwo;
    uint8_t lastState;
};

#endif
