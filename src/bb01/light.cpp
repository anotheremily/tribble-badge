/**
 * Light handling
 * Emily Young <emily@zavtralabs.com>
 *
 * Most colors adapted from:
 *      http://www.color-hex.com/color-palettes/?keyword=pride
 * Structure inspiration from QC12 Badge by George
 */

#include "light.h"

const color color_rgb[] = {
    {255, 0, 0},
    {0, 255, 0},
    {0, 0, 255}
};
const pattern pattern_rgb = {color_rgb, 3};

const color color_pride[] = {
    {255, 0, 0},
    {253, 255, 0},
    {60, 255, 0},
    {0, 133, 255},
    {140, 0, 219},
};
const pattern pattern_pride = {color_pride, 5};

const color color_trans[] = {
    {91,206,250},
    {245, 169, 184},
    {255, 255, 255},
    {91,206,250},
    {245, 169, 184}
};
const pattern pattern_trans = {color_trans, 5};

const color color_genderqueer[] = {
	{201, 138, 255},
    {255, 255, 255},
    {80, 150, 85}
};
const pattern pattern_genderqueer = {color_genderqueer, 5};

const color color_bisexual[] = {
    {219, 0, 110},
    {154, 63, 161},
    {58, 61, 168}
};
const pattern pattern_bisexual = {color_bisexual, 3};

const color color_pansexual[] = {
    {255, 0, 193},
    {255, 244, 0},
    {110, 186, 255}
};
const pattern pattern_pansexual = {color_pansexual, 3};


const color color_nonbinary[] = {};
const pattern pattern_nonbinary = {color_nonbinary, 0};

const color color_intersex[] = {};
const pattern pattern_intersex = {color_intersex, 0};

const color color_asexual[] = {};
const pattern pattern_asexual = {color_asexual, 0};

const color color_ally[] = {};
const pattern pattern_ally = {color_ally, 0};

const color color_leather[] = {};
const pattern pattern_leather = {color_leather, 0};

const color color_bear[] = {};
const pattern pattern_bear = {color_bear, 0};

const pattern patterns[] = {
    pattern_rgb,
    pattern_pride,
    pattern_trans,
    pattern_genderqueer,
    pattern_bisexual,
    pattern_pansexual,
    // pattern_nonbinary,
    // pattern_intersex,
    // pattern_asexual
    // pattern pattern_ally
    // pattern pattern_leather
    // pattern pattern_bear
};

LightHandler::LightHandler() {
    this->strip = Adafruit_NeoPixel(PIXELS, LED_PIN, NEO_RGBW + NEO_KHZ800);  // or NEO_GRBW
    this->strip.begin();
    this->strip.show();
    this->strip.setBrightness(BRIGHTNESS);

    // restore pattern and mode from eeprom
    this->pattern = getPattern();
    this->mode = getMode();
}

LightHandler::~LightHandler() {
}

void LightHandler::step() {
}

uint8_t LightHandler::stepPattern() {
    // @TODO check eeprom
    this->pattern += 1;
    if (this->pattern == ACTIVE_PATTERNS) {  // loop back around
        this->pattern = 0;
    }
    return this->pattern;

}

uint8_t LightHandler::stepMode() {
    // @TODO check eeprom
    this->mode += 1;
    if (this->mode == ACTIVE_MODES) {  // loop back around
        this->mode = 0;
    }
    return this->mode;
}

void LightHandler::debug() {

    for (uint8_t p = strip.numPixels(); p > 0; p -= 1) {
        for (uint8_t i = 0; i < 255; i += 1) {
            this->strip.setPixelColor(p - 1, i, i, i);
        }
        this->strip.show();
        delay(1);
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
