#include "constants.h"
#include "button.h"
#include "light.h"
#include "store.h"


LightHandler *lights;
ButtonHandler *buttons;

void setup() {
    buttons = new ButtonHandler();
    lights = new LightHandler();
    // storeInit(0);
}

/**
 * Main event loop.
 *
 * Poll for button input and respond accordingly
 * Update lights
 */
void loop() {

    // Button handling - poll buttons to see if one or more is pressed
    uint8_t buttonPressed = buttons->poll();

    if (buttonPressed == BUTTON_1) {
       lights->stepPattern();
    } else if (buttonPressed == BUTTON_2) {
       lights->stepMode();
    } else if (buttonPressed == BUTTON_1_2) {
        lights->stepBrightness();
    }

    // update lights
    lights->step();
    delay(50); // temp
}
