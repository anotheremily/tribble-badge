/**
 * Light handling
 * Emily Young <emily@zavtralabs.com>
 */

#include "light.h"

#define PIN      6
#define N_LEDS 14


LightManager::LightManager() {
    // Parameter 1 = number of pixels in strip
    // Parameter 2 = pin number (most are valid)
    // Parameter 3 = pixel type flags, add together as needed:
    //   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
    //   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
    //   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
    //   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
    this->strip = Adafruit_NeoPixel(20, LED_PIN);
    this->strip.begin();
    this->strip.show();
    this->strip.setBrightness(50);
}

LightManager::~LightManager() {
}

void LightManager::crossfade() {
}

void LightManager::blink(int times) {
    if (times < 1) {
        return;
    }

        for (uint8_t p = strip.numPixels(); p > 0; p -= 1) {
            for (uint8_t i = 0; i < 255; i += 1) {
                this->strip.setPixelColor(p - 1, i, i, i);
                this->strip.show();
                delay(1);
            }
        }


    delay(5000);

    for (uint8_t i = 255; i > 0; i -= 1) {
        for (uint8_t p = 0; p < this->strip.numPixels(); p += 1) {
            this->strip.setPixelColor(p, i - 1, i - 1, i - 1);
        }
        this->strip.show();
        delay(1);
    }

}
