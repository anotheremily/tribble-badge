/**
 * Button handling
 * Emily Young <emily@zavtralabs.com>
 */

#ifndef LIGHT_H
#define LIGHT_H

#include "Arduino.h"
#include "Adafruit_NeoPixel.h"
#include "constants.h"

class LightManager {
public:
    LightManager();
    ~LightManager();

    void crossfade();
    void blink(int);
private:
    Adafruit_NeoPixel strip;
};

#endif
