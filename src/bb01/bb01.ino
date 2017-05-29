#include "constants.h"
#include "button.h"
#include "light.h"
#include "store.h"
#include "pairing.h"

LightHandler *lights;
button_t buttonOne;
button_t buttonTwo;
uint8_t lastButtonPressed;

void setup() {
    buttonOne = createButton(BUTTON_1_PIN);
    buttonTwo = createButton(BUTTON_2_PIN);
    lastButtonPressed = BUTTON_NONE;

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
    pollButton(buttonOne);
    pollButton(buttonTwo);

    // Not doing anything with dual press now
    // if (buttonOne.state == HIGH &&
    //         buttonTwo.state == HIGH &&
    //         BUTTON_1_2 != lastButtonPressed) {
    //     lastButtonPressed = BUTTON_1_2;
    //     // lights->debug();
    // } else
    if (buttonOne.state == HIGH && BUTTON_1 != lastButtonPressed) {
        lastButtonPressed = BUTTON_1;
        lights->stepPattern();
    } else if (buttonTwo.state == HIGH && BUTTON_2 != lastButtonPressed) {
        lastButtonPressed = BUTTON_2;
        lights->stepMode();
    } else {
        lastButtonPressed = BUTTON_NONE;
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
