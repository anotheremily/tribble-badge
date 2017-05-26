#include "constants.h"
#include "button.h"
#include "light.h"

ButtonHandler *buttons;
LightHandler *lights;

void setup() {
    buttons = new ButtonHandler();
    lights = new LightHandler();
}

/**
 * Main event loop.
 *
 * Poll for button input and respond accordingly
 * Check for pairing
 * @TODO microphone sample?
 * Update lights
 */
void loop() {

    // poll buttons to see if one or more is pressed
    uint8_t buttonPressed = buttons->poll();

    switch (buttonPressed) {
        case BUTTON_1:  // Button 1 press
            // lights->debug();
            lights->stepPattern();
            break;
        case BUTTON_2:
            // lights->debug();
            lights->stepMode();
            break;
        case BUTTON_1_2:
            lights->debug();
            break;
        case BUTTON_NONE:
        default:
            break;
    }

    // @TODO check for pairing
    // pairing->check();

    // update lights
    lights->step();
}
