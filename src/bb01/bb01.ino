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
 * Check for pairing
 * @TODO microphone sample?
 * Update lights
 */
void loop() {

    // Button handling - poll buttons to see if one or more is pressed
    uint8_t buttonPressed = buttons->poll();

    switch (buttonPressed) {
        case BUTTON_1:  // Button 1 press
            lights->stepPattern();
            break;
        case BUTTON_2:
            lights->stepMode();
            break;
        case BUTTON_1_2:
            // lights->debug();
            break;
        case BUTTON_NONE:
        default:
            break;
    }

    // Pairing
    // if (isConnected()) {
    //     if (attemptPairing()) {
    //         // @TODO incr level
    //         // @TODO check for new unlocks
    //         // @TODO lights - happy pattern
    //     } else {
    //         // @TODO lights - sad pattern
    //     }
    // }

    // @TODO microphone

    // update lights
    lights->step();
    delay(50); // temp
}
