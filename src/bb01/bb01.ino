// #include <StandardCplusplus.h>
// #include <MemoryFree.h>
#include <Wire.h>

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

    // poll buttons
    buttons->poll();

    // @TODO check for button clicks/releases

    // continue current light crossfade
    lights->crossfade();
}
