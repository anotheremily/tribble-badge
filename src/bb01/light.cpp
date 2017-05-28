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

// const color_t color_nonbinary[] = {};
// const pattern_t pattern_nonbinary = {color_nonbinary, 0};
//
// const color_t color_intersex[] = {};
// const pattern_t pattern_intersex = {color_intersex, 0};
//
// const color_t color_asexual[] = {};
// const pattern_t pattern_asexual = {color_asexual, 0};
//
// const color_t color_ally[] = {};
// const pattern_t pattern_ally = {color_ally, 0};
//
// const color_t color_leather[] = {};
// const pattern_t pattern_leather = {color_leather, 0};
//
// const color_t color_bear[] = {};
// const pattern_t pattern_bear = {color_bear, 0};

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
    this->strip = Adafruit_NeoPixel(NUM_PIXELS, LED_PIN, NEO_GRBW + NEO_KHZ800);  // or NEO_GRBW
    this->strip.begin();
    this->strip.show();
    // this->strip.setBrightness(BRIGHTNESS);

    // restore pattern and mode from eeprom
    this->pattern = 0; // getPattern();
    this->mode = 0; // getMode();
    this->patternStep = 0;
    this->modeStep = 0;
    this->patternHold = 0;

    this->crossfadeAmount = getCrossfadeAmount(
        translateColor(this->strip.getPixelColor(0)),
        patterns[this->pattern].colors[this->patternStep]);
}

LightHandler::~LightHandler() {
}

void LightHandler::step() {
    if (this->mode == MODE_BLINK) {
        this->stepModeBlink();
    } else if (this->mode == MODE_CROSSFADE_ALL) {
        this->stepModeCrossfadeAll();
    } else if (this->mode == MODE_CROSSFADE_HORZ) {
        // @TODO implement
    } else if (this->mode == MODE_CROSSFADE_VERT) {
        // @TODO implement
    } else if (this->mode == MODE_CHASE) {
        // @TODO implement
    } else if (this->mode == MODE_CHASE_ACROSS) {
        // @TODO implement
    } else if (this->mode == MODE_CHASE_DOWN) {
        // @TODO implement
    } else if (this->mode == MODE_SPARKS) {
        // @TODO implement
    } else if (this->mode == MODE_DANCE) {
        // @TODO implement
    } else if (this->mode == MODE_EQUALIZER) {
        // @TODO implement
    } else {
        // skip
    }
}

void LightHandler::stepModeBlink() {
    // get common color and target goals
    color_t target = (this->modeStep == 1)
        ? colorOff
        : patterns[this->pattern].colors[this->patternStep];

    color_t color = stepColor(
        translateColor(this->strip.getPixelColor(0)),
        target, this->crossfadeAmount);

    for (uint8_t i = 0; i < NUM_PIXELS; i += 1) {
        this->strip.setPixelColor(i, color.red, color.green, color.blue, 0);
    }
    this->strip.show();

    // go to next color at the end of the pattern (or off state if in between)
    if (isEqual(color, target)) {
        if (this->modeStep == 0 && this->patternHold < CROSSFADE_HOLD) {
            // hold color for a number of steps
            this->patternHold += 1;
        } else {
            // otherwise, go to the next step in the pattern
            this->patternHold = 0;
            if (this->modeStep == 0) {
                // blink fades to black before going to next color
                this->modeStep = 1;
                target = colorOff;
            } else {
                this->modeStep = 0;
                this->patternStep += 1;
                if (this->patternStep == patterns[this->pattern].len) {
                    this->patternStep = 0;
                }
                target = patterns[this->pattern].colors[this->patternStep];
            }
            this->crossfadeAmount = getCrossfadeAmount(color, target);
        }
    }
}

void LightHandler::stepModeCrossfadeAll() {
    // for crossfade, everything's the same, so no reason to step each one
    color_t target = patterns[this->pattern].colors[this->patternStep];
    color_t color = translateColor(this->strip.getPixelColor(0));
    color = stepColor(color, target, this->crossfadeAmount);

    for (uint8_t i = 0; i < NUM_PIXELS; i += 1) {
        this->strip.setPixelColor(i, color.red, color.green, color.blue, 0);
    }
    this->strip.show();

    if (isEqual(color, target)) { // if need to step pattern
        if (this->patternHold < CROSSFADE_HOLD) {
            // hold color for a number of steps
            this->patternHold += 1;
        } else {
            // otherwise, go to the next step in the pattern
            this->patternHold = 0;
            this->patternStep += 1;
            if (this->patternStep == patterns[this->pattern].len) {
                this->patternStep = 0;
            }
            this->crossfadeAmount = getCrossfadeAmount(
                color, patterns[this->pattern].colors[this->patternStep]);
        }
    }
}

void LightHandler::stepPattern() {
    this->pattern += 1;
    if (this->pattern == ACTIVE_PATTERNS) {  // loop back around
        this->pattern = 0;
    }
    this->patternStep = 0;

    // get new timings
    this->crossfadeAmount = getCrossfadeAmount(
        translateColor(this->strip.getPixelColor(0)),
        patterns[this->pattern].colors[this->patternStep]);

    // @TODO uncomment
    // setPattern(this->pattern);
}

void LightHandler::stepMode() {
    this->mode += 1;
    if (this->mode == ACTIVE_MODES) {  // loop back around
        this->mode = 0;
    }

    // reset state
    this->patternStep = 0;
    this->modeStep = 0;

    this->crossfadeAmount = getCrossfadeAmount(
        translateColor(this->strip.getPixelColor(0)),
        patterns[this->pattern].colors[this->patternStep]);

    // @TODO uncomment
    // setMode(this->mode);
}

void LightHandler::debug() {

    for (uint8_t p = NUM_PIXELS; p > 0; p -= 1) {
        for (uint8_t i = 0; i < 255; i += 1) {
            this->strip.setPixelColor(p - 1, i, i, i, 0);
            this->strip.show();
            delay(1);
        }
    }

    delay(1000);

    for (uint8_t i = 255; i > 0; i -= 1) {
        for (uint8_t p = 0; p < NUM_PIXELS; p += 1) {
            this->strip.setPixelColor(p, i - 1, i - 1, i - 1, 0);
        }
        this->strip.show();
    }
}

color_t translateColor(uint32_t c32) {
    return color_t {
        (uint8_t) ((c32 >> 16) & 0xff),
        (uint8_t) ((c32 >>  8) & 0xff),
        (uint8_t) (c32 & 0xff)
    };
}

bool isEqual(color_t current, color_t target) {
    return current.red == target.red &&
        current.green == target.green &&
        current.blue == target.blue;
}

color_t stepColor(color_t current, color_t target, crossfade_t amount) {
    return color_t {
        stepChannel(current.red, target.red, amount.red),
        stepChannel(current.green, target.green, amount.green),
        stepChannel(current.blue, target.blue, amount.blue)
    };
}

uint8_t stepChannel(uint8_t current, uint8_t target, uint8_t amount) {
    if (current < target && current + amount < target) {  // increment up
        return current + amount;
    } else if (current > target && current - amount > target) {  // increment down
        return current - amount;
    }
    return target;
}

crossfade_t getCrossfadeAmount(color_t current, color_t target) {
    return crossfade_t {
        abs(current.red - target.red) / CROSSFADE_STEPS,
        abs(current.green - target.green) / CROSSFADE_STEPS,
        abs(current.blue - target.blue) / CROSSFADE_STEPS
    };
}
