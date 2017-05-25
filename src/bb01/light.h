/**
 * Button handling
 * Emily Young <emily@zavtralabs.com>
 */

#ifndef LIGHT_H
#define LIGHT_H

#include "Arduino.h"
#include "constants.h"

class LightManager {
public:
    LightManager();
    ~LightManager();

    void crossfade();
    void blink(int);
};

#endif
