/**
 * Button handling
 * Emily Young <emily@zavtralabs.com>
 *
 * Debounce code adapted from https://www.arduino.cc/en/tutorial/debounce
 */

#include "button.h"

button_t createButton(uint8_t pin) {
    pinMode(pin, INPUT);
    return button_t {pin, LOW, LOW, 0};
}

void pollButton(button_t button) {
    uint8_t reading = digitalRead(button.pin);
    uint16_t ms = millis();

    // check to see if you just pressed the button
    // (i.e. the input went from LOW to HIGH),  and you've waited
    // long enough since the last press to ignore any noise:

    // If the switch changed, due to noise or pressing:
    if (reading != button.lastState) {
        // reset the debouncing timer
        button.lastDebounceTime = ms;
    }

    if ((ms - button.lastDebounceTime) > DEBOUNCE_DELAY) {
        // whatever the reading is at, it's been there for longer
        // than the debounce delay, so take it as the actual current state:

        // if the button state has changed
        if (reading != button.state) {
            button.state = reading;
        }
    }

    // save the reading.  Next time through the loop,
    // it'll be the lastState:
    button.lastState = reading;
}
