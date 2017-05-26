/**
 * Button handling
 * Emily Young <emily@zavtralabs.com>
 *
 * Debounce code adapted from https://www.arduino.cc/en/tutorial/debounce
 */

#include "button.h"

Button::Button(uint8_t pin) {
    pinMode(pin, INPUT);

    this->pin = pin;
    this->lastButtonState = LOW;
    this->buttonState == LOW;
    this->lastDebounceTime = 0;
}

Button::~Button() {
}

uint8_t Button::poll() {
    uint8_t reading = digitalRead(this->pin);

    // check to see if you just pressed the button
    // (i.e. the input went from LOW to HIGH),  and you've waited
    // long enough since the last press to ignore any noise:

    // If the switch changed, due to noise or pressing:
    if (reading != this->lastButtonState) {
        // reset the debouncing timer
        this->lastDebounceTime = millis();
    }

    if ((millis() - this->lastDebounceTime) > DEBOUNCE_DELAY) {
        // whatever the reading is at, it's been there for longer
        // than the debounce delay, so take it as the actual current state:

        // if the button state has changed:
        if (reading != this->buttonState) {
            this->buttonState = reading;
        }
    }

    // save the reading.  Next time through the loop,
    // it'll be the lastButtonState:
    this->lastButtonState = reading;
}

bool Button::isPressed() {
    return this->buttonState == HIGH ? true : false;
}

ButtonHandler::ButtonHandler() {
    this->buttonOne = new Button(BUTTON_1);
    this->buttonTwo = new Button(BUTTON_2);
    this->lastState = BUTTON_NONE;
}

ButtonHandler::~ButtonHandler() {
}

uint8_t ButtonHandler::poll() {
    this->buttonOne->poll();
    this->buttonTwo->poll();

    uint8_t newState = BUTTON_NONE;
    if (this->buttonOne->isPressed() && this->buttonTwo->isPressed()) {
        newState = BUTTON_1_2;
    } else if (this->buttonOne->isPressed()) {
        newState = BUTTON_1;
    } else if (this->buttonTwo->isPressed()) {
        newState = BUTTON_2;
    }

    if (newState != this->lastState) {
        this->lastState = newState;
        return newState;
    }
    return BUTTON_NONE;
}
