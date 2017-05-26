/**
 * Light handling
 * Emily Young <emily@zavtralabs.com>
 * Most colors adapted from:
 *      http://www.color-hex.com/color-palettes/?keyword=pride
 * Structure inspiration from QC12 Badge by George
 */

#include "light.h"

// #define PATTERN_RGB         0
const color pattern_rgb[] = {
    {255, 0, 0},
    {0, 255, 0},
    {0, 0, 255}
};

// #define PATTERN_PRIDE       1
const color pattern_pride[] = {
    {255, 0, 0},
    {253, 255, 0},
    {60, 255, 0},
    {0, 133, 255},
    {140, 0, 219},
};

// #define PATTERN_TRANS       2
const color pattern_trans[] = {
    {91,206,250},
    {245, 169, 184},
    {255, 255, 255},
    {91,206,250},
    {245, 169, 184}
};


// #define PATTERN_GENDERQUEER 3
const color pattern_genderqueer = {
	{201, 138, 255}
    {255, 255, 255},
    {80, 150, 85}
}

// #define PATTERN_NONBINARY   4

// #define PATTERN_INTERSEX    5

// #define PATTERN_BISEXUAL    6
const color pattern_bisexual[] = {
    {255, 57, 187},
    {214, 0, 255},
    {0, 4, 255}
};

// #define PATTERN_PANSEXUAL   7
const color pattern_pansexual[] = {
    {255, 0, 193},
    {255, 244, 0},
    {110, 186, 255}
};

// #define PATTERN_ASEXUAL     8

// #define PATTERN_ALLY        9

// #define PATTERN_LEATHER     10

// #define PATTERN_BEAR        11


LightHandler::LightHandler() {
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

LightHandler::~LightHandler() {
}

void LightHandler::step() {
}

void LightHandler::setPattern(uint8_t pattern) {

}

// void LightHandler::blink(int times) {
//     if (times < 1) {
//         return;
//     }
//
//         for (uint8_t p = strip.numPixels(); p > 0; p -= 1) {
//             for (uint8_t i = 0; i < 255; i += 1) {
//                 this->strip.setPixelColor(p - 1, i, i, i);
//                 this->strip.show();
//                 delay(1);
//             }
//         }
//
//
//     delay(5000);
//
//     for (uint8_t i = 255; i > 0; i -= 1) {
//         for (uint8_t p = 0; p < this->strip.numPixels(); p += 1) {
//             this->strip.setPixelColor(p, i - 1, i - 1, i - 1);
//         }
//         this->strip.show();
//         delay(1);
//     }
//
// }
