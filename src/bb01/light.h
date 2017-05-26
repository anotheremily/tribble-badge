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
     * @param uint8_t pattern
     */
    void setPattern(uint8_t);

    /**
     * Debug leds
     */
    void debug();
private:
    Adafruit_NeoPixel strip;
};

#endif
