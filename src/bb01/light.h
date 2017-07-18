/**
 * Light handling
 * Emily Young <emily@zavtralabs.com>
 */

#ifndef LIGHT_H
#define LIGHT_H

#include "neopixel.h"
#include "constants.h"
#include "store.h"
#include "util.h"

typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} color_t;

typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} crossfade_t;

/**
 * Translate 32 bit color to r,g,b values
 * @param uint32 color
 * @return color_t color
 */
color_t translateColor(uint32_t);

/**
 * Check if two colors are equal
 * @param color_t current color
 * @param color_t target color
 * @return bool is equal?
 */
bool isEqual(color_t current, color_t target);

/**
 * Increments color
 * @param color_t current color
 * @param color_t target color
 * @param uint8_t amount
 * @return color_t incremeneted color
 */
color_t stepColor(color_t, color_t, crossfade_t);

/**
 * Increments color channel (r,g,b)
 * @param uint8_t current color
 * @param uint8_t target color
 * @param uint8_t amount
 * @return color_t color
 */
uint8_t stepChannel(uint8_t, uint8_t, uint8_t);

/**
 * Get current crossfade delta for all colors to arrive at the color at the
 * same time.
 * @param color_t current
 * @param color_t target
 * @return crossfade_t speeds
 */
crossfade_t getCrossfadeAmount(color_t, color_t);

uint8_t getCrossfadeChannel(uint8_t current, uint8_t target);

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
     * Set brightness
     */
    void stepBrightness();

    /**
     * Debug mode for leds
     */
    // void debug();
private:
    Adafruit_NeoPixel *strip;

    uint8_t brightness;
    uint8_t pattern;
    uint8_t mode;

    uint8_t modeDir;
    uint8_t modeStep;  // used by modes to keep track of state
    uint8_t patternStep;  // used by modes to keep track of state
    uint8_t patternHold;
    crossfade_t crossfadeAmount;

    // mode step functions
    void stepModeBlink();
    void stepModeCrossfade(uint8_t);
    void stepModeChase(uint8_t);
    void stepModeSparks();
};

#endif
