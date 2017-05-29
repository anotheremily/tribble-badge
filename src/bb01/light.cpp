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

const color_t color_pride[] = {
    {232, 4, 0},
    {255, 141, 0},
    {255, 239, 0},
    {0, 129, 33},
    {0, 68, 255},
    {119, 0, 137}
};

const color_t color_trans[] = {
    {91,206,250},
    {245, 169, 184},
    {255, 255, 255},
    {91,206,250},
    {245, 169, 184}
};

const color_t color_genderqueer[] = {
	{201, 138, 255},
    {255, 255, 255},
    {80, 150, 85}
};

const color_t color_bisexual[] = {
    {219, 0, 110},
    {154, 63, 161},
    {58, 61, 168}
};

const color_t color_pansexual[] = {
    {255, 0, 193},
    {255, 244, 0},
    {110, 186, 255}
};

// const color_t color_nonbinary[] = {};
// const color_t color_intersex[] = {};
// const color_t color_asexual[] = {};
// const color_t color_ally[] = {};
// const color_t color_leather[] = {};
// const color_t color_bear[] = {};

const color_t *patterns[] = {
    color_rgb,
    color_pride,
    color_trans,
    color_genderqueer,
    color_bisexual,
    color_pansexual,
    // color_nonbinary,
    // color_intersex,
    // color_asexual
    // color_ally
    // color_leather
    // color_bear
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
        patterns[this->pattern][this->patternStep]);
}

LightHandler::~LightHandler() {
}

void LightHandler::step() {
    if (this->mode == MODE_BLINK) {
        this->stepModeBlink();
    } else if (this->mode == MODE_CROSSFADE_ALL) {
        this->stepModeCrossfadeAll();
    } else if (this->mode == MODE_CROSSFADE_ACROSS) {
        this->stepModeCrossfadeAcross();
    } else if (this->mode == MODE_CROSSFADE_DOWN) {
        this->stepModeCrossfadeDown();
    } else if (this->mode == MODE_CHASE_AROUND) {
        this->stepModeChaseAround();
    } else if (this->mode == MODE_CHASE_ACROSS) {
        this->stepModeChaseAcross();
    } else if (this->mode == MODE_CHASE_DOWN) {
        this->stepModeChaseDown();
    } else if (this->mode == MODE_SPARKS) {
        this->stepModeSparks();
    } else if (this->mode == MODE_DANCE) {
        this->stepModeDance();
    } else if (this->mode == MODE_EQUALIZER) {
        this->stepModeEqualizer();
    }
}

void LightHandler::stepModeBlink() {
    // get common color and target goals
    color_t target = (this->modeStep == 1)
        ? colorOff
        : patterns[this->pattern][this->patternStep];

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
                if (this->patternStep == sizeof(patterns[this->pattern]) + 1) {
                    this->patternStep = 0;
                }
                target = patterns[this->pattern][this->patternStep];
            }
            this->crossfadeAmount = getCrossfadeAmount(color, target);
        }
    }
}

void LightHandler::stepModeCrossfadeAll() {
    // for crossfade, everything's the same, so no reason to step each one
    color_t target = patterns[this->pattern][this->patternStep];
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
            if (this->patternStep == sizeof(patterns[this->pattern]) + 1) {
                this->patternStep = 0;
            }
            this->crossfadeAmount = getCrossfadeAmount(
                color, patterns[this->pattern][this->patternStep]);
        }
    }
}

void LightHandler::stepModeCrossfadeAcross() {
    // @TODO implement
}

void LightHandler::stepModeCrossfadeDown() {
    // @TODO implement
}

void LightHandler::stepModeChaseAround() {
    // @TODO implement
}

void LightHandler::stepModeChaseAcross() {
    // @TODO implement
}

void LightHandler::stepModeChaseDown() {
    // @TODO implement
}

void LightHandler::stepModeSparks() {
    if (this->modeStep == 1) {
        // if already on, turn off or hold
        this->strip.setPixelColor(this->patternStep, 0, 0, 0, 0);
        this->strip.show();
        this->patternHold = 0;
        this->modeStep = 0;
    } else {
        if (pseudorand() % 100 < SPARK_CHANCE) {
            uint8_t idx = pseudorand() % (sizeof(patterns[this->pattern]) + 1);
            uint8_t pixel = pseudorand() % NUM_PIXELS;
            color_t color = patterns[this->pattern][idx];
            this->strip.setPixelColor(pixel,
                                      color.red,
                                      color.green,
                                      color.blue,
                                      0);
            this->strip.show();
            this->patternStep = pixel;
            this->modeStep = 1;
        }
    }
}

void LightHandler::stepModeDance() {
    // @TODO implement
}

void LightHandler::stepModeEqualizer() {
    // @TODO implement
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
        patterns[this->pattern][this->patternStep]);

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
        patterns[this->pattern][this->patternStep]);

    // @TODO uncomment
    // setMode(this->mode);
}

void LightHandler::debug() {
    //
    // for (uint8_t p = NUM_PIXELS; p > 0; p -= 1) {
    //     for (uint8_t i = 0; i < 255; i += 1) {
    //         this->strip.setPixelColor(p - 1, i, i, i, 0);
    //         this->strip.show();
    //         delay(1);
    //     }
    // }
    //
    // delay(1000);
    //
    // for (uint8_t i = 255; i > 0; i -= 1) {
    //     for (uint8_t p = 0; p < NUM_PIXELS; p += 1) {
    //         this->strip.setPixelColor(p, i - 1, i - 1, i - 1, 0);
    //     }
    //     this->strip.show();
    // }
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
    // add one to each to make sure we ner get in a stuck state
    return crossfade_t {
        getCrossfadeChannel(current.red, target.red),
        getCrossfadeChannel(current.green, target.green),
        getCrossfadeChannel(current.blue, target.blue)
    };
}

uint8_t getCrossfadeChannel(uint8_t current, uint8_t target) {
    return abs(current - target) / CROSSFADE_STEPS + 1;
}
