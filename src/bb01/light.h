/**
 * Button handling
 * Emily Young <emily@zavtralabs.com>
 */

#ifndef LIGHT_H
#define LIGHT_H

#include "Arduino.h"
#include "Adafruit_NeoPixel.h"
#include "constants.h"

typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} color;

typedef struct {
    color *colors;
    uint8_t len;
} pattern;

class LightHandler {
public:
    LightHandler();
    ~LightHandler();

    /**
     * Step through current pattern
     */
    void step();

    /**
     * Set pattern
     * @return new mode
     */
    uint8_t stepPattern();

    /**
     * Set mode
     * @return new mode
     */
    uint8_t stepMode();

    // @TODO add getters?

    /**
     * Debug leds
     */
    void debug();
private:
    Adafruit_NeoPixel strip;

    uint8_t pattern;
    uint8_t mode;
};

#endif
