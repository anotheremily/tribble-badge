/**
 * Button handling
 * Emily Young <emily@zavtralabs.com>
 */

#ifndef BUTTON_H
#define BUTTON_H

#include "Arduino.h"
#include "constants.h"

typedef struct {
    uint8_t pin;
    uint8_t lastState;
    uint8_t state;
    uint16_t lastDebounceTime;
} button_t;

button_t createButton(uint8_t);
void pollButton(button_t);

#endif
