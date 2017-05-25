/**
 * Light handling
 * Emily Young <emily@zavtralabs.com>
 */

#include "light.h"

LightManager::LightManager() {
    pinMode(LED_PIN, OUTPUT);
}

LightManager::~LightManager() {
}

void LightManager::crossfade() {
}

void LightManager::blink(int times) {
    if (times < 1) {
        return;
    }

    for (int i = 0; i < times; i += 1) {
        digitalWrite(LED_PIN, HIGH);
        delay(BLINK_DELAY);
        digitalWrite(LED_PIN, LOW);
        delay(BLINK_DELAY);
    }
}
