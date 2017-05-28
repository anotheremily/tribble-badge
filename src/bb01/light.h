/**
 * Light handling
 * Emily Young <emily@zavtralabs.com>
 */

#ifndef LIGHT_H
#define LIGHT_H

#include "Arduino.h"
#include "Adafruit_NeoPixel.h"
#include "constants.h"
#include "store.h"

typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} color_t;

typedef struct {
    color_t *colors;
    uint8_t len;
} pattern_t;

/**
 * Translate 32 bit color to r,g,b values
 * @param uint32 color
 * @return color_t color
 */
inline color_t translateColor(uint32_t);

/**
 * Check if two colors are equal
 * @param color_t current color
 * @param color_t target color
 * @return bool is equal?
 */
inline bool isEqual(color_t current, color_t target);

/**
 * Increments color
 * @param color_t current color
 * @param color_t target color
 * @param uint8_t amount
 * @return color_t incremeneted color
 */
inline color_t stepColor(color_t, color_t, uint8_t);

/**
 * Increments color channel (r,g,b)
 * @param uint8_t current color
 * @param uint8_t target color
 * @param uint8_t amount
 * @return color_t color
 */
inline uint8_t stepChannel(uint8_t, uint8_t, uint8_t);

/**
 * Light handler class
 */
class LightHandler {
public:
    LightHandler();
    ~LightHandler();

    /**
     * Step through current mode
     */
    void step();

    /**
     * Set pattern
     */
    void stepPattern();

    /**
     * Set mode
     */
    void stepMode();

    /**
     * Reset LEDs to off
     */
    void reset();

    /**
     * Debug mode for leds
     */
    void debug();
private:
    Adafruit_NeoPixel strip;

    uint8_t pattern;
    uint8_t mode;
    uint8_t modeStep;  // used by modes to keep track of state
    uint8_t patternStep;  // used by modes to keep track of state
    // color_t[] led_targets;

    // mode step functions
    void stepModeBlink();
    void stepModeCrossfadeAll();
};

#endif
