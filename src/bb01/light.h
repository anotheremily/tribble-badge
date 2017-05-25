/**
 * Button handling
 * Emily Young <emily@zavtralabs.com>
 */

#ifndef LIGHT_H
#define LIGHT_H

#include "lib/neopixel/Adafruit_NeoPixel.h"

class LightManager {
public:
    LightManager();
    ~LightManager();

    void crossfade();
};

#endif
