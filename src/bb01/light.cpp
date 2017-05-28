/**
 * Light handling
 * Emily Young <emily@zavtralabs.com>
 *
 * Most colors adapted from:
 *      http://www.color-hex.com/color-palettes/?keyword=pride
 * Structure inspiration from QC12 Badge by George
 */

#include "light.h"

const color_t colorOff = {CHANNEL_OFF, CHANNEL_OFF, CHANNEL_OFF};

const color_t color_rgb[] = {
    {255, 0, 0},
    {0, 255, 0},
    {0, 0, 255}
};
const pattern_t pattern_rgb = {color_rgb, 3};

const color_t color_pride[] = {
    {255, 0, 0},
    {253, 255, 0},
    {60, 255, 0},
    {0, 133, 255},
    {140, 0, 219},
};
const pattern_t pattern_pride = {color_pride, 5};

const color_t color_trans[] = {
    {91,206,250},
    {245, 169, 184},
    {255, 255, 255},
    {91,206,250},
    {245, 169, 184}
};
const pattern_t pattern_trans = {color_trans, 5};

const color_t color_genderqueer[] = {
	{201, 138, 255},
    {255, 255, 255},
    {80, 150, 85}
};
const pattern_t pattern_genderqueer = {color_genderqueer, 5};

const color_t color_bisexual[] = {
    {219, 0, 110},
    {154, 63, 161},
    {58, 61, 168}
};
const pattern_t pattern_bisexual = {color_bisexual, 3};

const color_t color_pansexual[] = {
    {255, 0, 193},
    {255, 244, 0},
    {110, 186, 255}
};
const pattern_t pattern_pansexual = {color_pansexual, 3};


const color_t color_nonbinary[] = {};
const pattern_t pattern_nonbinary = {color_nonbinary, 0};

const color_t color_intersex[] = {};
const pattern_t pattern_intersex = {color_intersex, 0};

const color_t color_asexual[] = {};
const pattern_t pattern_asexual = {color_asexual, 0};

const color_t color_ally[] = {};
const pattern_t pattern_ally = {color_ally, 0};

const color_t color_leather[] = {};
const pattern_t pattern_leather = {color_leather, 0};

const color_t color_bear[] = {};
const pattern_t pattern_bear = {color_bear, 0};

const pattern_t patterns[] = {
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
    this->strip = Adafruit_NeoPixel(PIXELS, LED_PIN, NEO_GRBW + NEO_KHZ800);  // or NEO_GRBW
    this->strip.begin();
    this->strip.show();
    this->strip.setBrightness(BRIGHTNESS);

    // restore pattern and mode from eeprom
    this->pattern = getPattern();
    this->mode = getMode();
    this->patternStep = 0;
    this->modeStep = 0;
}

LightHandler::~LightHandler() {
}

void LightHandler::step() {
    pattern_t p = patterns[this->pattern];

    if (this->mode == MODE_BLINK) {
        this->stepModeBlink();
    } else if (this->mode == MODE_CROSSFADE_ALL) {
        this->stepModeCrossfadeAll();
    }

    // #define MODE_CROSSFADE_ALL 1
    // #define MODE_CROSSFADE_HORZ 2
    // #define MODE_CROSSFADE_VERT 3
    // #define MODE_CHASE 4
    // #define MODE_SPARKS 5
    // #define MODE_DANCE 6
    // #define MODE_EQUALIZER 7
}

void LightHandler::stepModeBlink() {
    pattern_t p = patterns[this->pattern];

    // for blink, everything's the same, so no reason to step each one
    color_t target = patterns[this->pattern].colors[this->patternStep];
    if (this->modeStep == 1) {
        target = colorOff;
    }
    color_t color = translateColor(this->strip.getPixelColor(0));
    color = stepColor(color, target, CROSSFADE_AMOUNT);

    if (isEqual(color, target)) { // if need to step pattern
        if (this->modeStep == 0) {
            this->modeStep = 1;
        } else {
            this->modeStep = 0;
            this->patternStep += 1;
            if (this->patternStep == patterns[this->pattern].len) {
                this->patternStep = 0;
            }
        }
    }

    for (uint8_t i = 0; i < this->strip.numPixels(); i += 1) {
        this->strip.setPixelColor(i, color.red, color.green, color.blue);
    }
    this->strip.show();
}

void LightHandler::stepModeCrossfadeAll() {
    pattern_t p = patterns[this->pattern];

    // for crossfade, everything's the same, so no reason to step each one
    color_t target = patterns[this->pattern].colors[this->patternStep];
    color_t color = translateColor(this->strip.getPixelColor(0));
    color = stepColor(color, target, BLAH);

    if (isEqual(color, target)) { // if need to step pattern
        this->patternStep += 1;
        if (this->patternStep == patterns[this->pattern].len) {
            this->patternStep = 0;
        }
    }

    for (uint8_t i = 0; i < this->strip.numPixels(); i += 1) {
        this->strip.setPixelColor(i, color.red, color.green, color.blue);
    }
    this->strip.show();
}

void LightHandler::stepPattern() {
    this->pattern += 1;
    if (this->pattern == ACTIVE_PATTERNS) {  // loop back around
        this->pattern = 0;
    }
    this->patternStep = 0;
}

void LightHandler::stepMode() {
    this->mode += 1;
    if (this->mode == ACTIVE_MODES) {  // loop back around
        this->mode = 0;
    }

    // reset state
    this->patternStep = 0;
    this->modeStep = 0;

    setMode(this->mode);
}

void LightHandler::reset() {
    // @TODO implement?
}

void LightHandler::debug() {

    for (uint8_t p = this->strip.numPixels(); p > 0; p -= 1) {
        for (uint8_t i = 0; i < 255; i += 1) {
            this->strip.setPixelColor(p - 1, i, i, i);
            this->strip.show();
            delay(1);
        }
    }

    delay(1000);

    for (uint8_t i = 255; i > 0; i -= 1) {
        for (uint8_t p = 0; p < this->strip.numPixels(); p += 1) {
            this->strip.setPixelColor(p, i - 1, i - 1, i - 1);
        }
        this->strip.show();
    }
}

inline color_t translateColor(uint32_t c32) {
    color_t c;
    c.red = (uint8_t) (c32 >> 16);
    c.green = (uint8_t) (c32 >>  8);
    c.blue = (uint8_t) c32;
    return c;
}

inline bool isEqual(color_t current, color_t target) {
    return current.red == target.red &&
        current.blue == target.blue &&
        current.green == target.green;
}

inline color_t stepColor(color_t current, color_t target, uint8_t amount) {
    current.red = stepChannel(current.red, target.red, amount);
    current.blue = stepChannel(current.blue, target.blue, amount);
    current.green = stepChannel(current.green, target.green, amount);
    return current;
}

inline uint8_t stepChannel(uint8_t current, uint8_t target, uint8_t amount) {
    if (current < target) {  // increment up
        current = current + amount > target ? target : current + amount;
    } else if (current > target) {  // increment down
        current = current - amount < target ? target : current - amount;
    }
    return current;
}
