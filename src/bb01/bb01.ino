#include "constants.h"
#include "button.h"
#include "light.h"

ButtonManager *buttons;
LightManager *lights;

void setup() {
    buttons = new ButtonManager();
    lights = new LightManager();
}

/**
 * Poll for button input
 *     - Perform actions
 * Update lights
 */
void loop() {

    uint8_t buttonClicked;

    // poll buttons to see if one or more is pressed
    buttonClicked = buttons->poll();

    // @TODO check for button clicks/releases
    if (buttonClicked != BUTTON_NONE) {
        lights->blink(1);
        if (buttonClicked == BUTTON_1) {
        } else if (buttonClicked == BUTTON_2) {
        } else if (buttonClicked == BUTTON_1_2) {
        }
    }

    // continue current light crossfade
    // lights->crossfade();
}
