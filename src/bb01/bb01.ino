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

    uint8_t buttonClicked;

    // poll buttons to see if one or more is pressed
    buttonClicked = buttons->poll();

    switch (buttonClicked) {
        case BUTTON_1:
            break;
        case BUTTON_2:
            break;
        case BUTTON_1_2:
            break;
        case BUTTON_NONE:
        default:
            break;
    }

    // @TODO check for pairing

    // @TODO update lights
}
