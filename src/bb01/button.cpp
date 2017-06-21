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
    this->prevState[0] = LOW;
    this->prevState[1] = LOW;
    this->buttonState = LOW;
}

Button::~Button() {
}

uint8_t Button::poll() {
    uint8_t reading = digitalRead(this->pin);

    // Debounce checking 2 historical values rather than using timing
    if (reading == this->prevState[0] &&
        reading == this->prevState[1] &&
        reading != this->buttonState) {

        this->buttonState = reading;
    }

    // Save state
    this->prevState[1] = this->prevState[0];
    this->prevState[0] = reading;
}

bool Button::isPressed() {
    return this->buttonState == HIGH ? true : false;
}

bool Button::maybePressed() {
    return this->prevState[1] == HIGH ? true : false;
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
    } else if (this->buttonOne->isPressed() &&
               !this->buttonTwo->maybePressed()) {
        newState = BUTTON_1;
    } else if (this->buttonTwo->isPressed() &&
               !this->buttonOne->maybePressed()) {
        newState = BUTTON_2;
    }

    if (newState != this->lastState) {
        this->lastState = newState;
        return newState;
    }
    return BUTTON_NONE;
}
