/**
 * Light handling
 * Emily Young <emily@zavtralabs.com>
 *
 * Most colors adapted from:
 *      http://www.color-hex.com/color-palettes/?keyword=pride
 * Structure inspiration from QC12 Badge by George
 */

#include "light.h"

// Row, column definitions
//     0   1   2   3   4   5
//     ----------------------
// 0       03          10
// 1   04      02  11      09
// 2       05          13
// 3   05      01  12      08
// 4       00          07
const uint8_t row_1[] = {3, 10};
const uint8_t row_2[] = {4, 2, 11, 9};
const uint8_t row_3[] = {5, 13};
const uint8_t row_4[] = {5, 1, 12, 8};
const uint8_t row_5[] = {0, 7};
const uint8_t *rows[] = {row_1, row_2, row_3, row_4, row_5};

const uint8_t col_1[] = {4, 5};
const uint8_t col_2[] = {3, 5, 0};
const uint8_t col_3[] = {2, 1};
const uint8_t col_4[] = {11, 12};
const uint8_t col_5[] = {10, 13, 7};
const uint8_t col_6[] = {9, 8};
const uint8_t *cols[] = {col_1, col_2, col_3, col_4, col_5, col_6};

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

const color_t color_nonbinary[] = {
  {255, 255, 255},
  {255, 255, 255},
  {255, 255, 255},
};

const color_t color_intersex[] = {
  {255, 255, 255},
  {255, 255, 255},
  {255, 255, 255},
};

const color_t color_asexual[] = {
  {255, 255, 255},
  {255, 255, 255},
  {255, 255, 255},
};

const color_t color_ally[] = {
  {255, 255, 255},
  {255, 255, 255},
  {255, 255, 255},
};

const color_t *patterns[] = {
    color_rgb,
    color_pride,
    color_trans,
    color_genderqueer,
    color_bisexual,
    color_pansexual,
    color_nonbinary,
    color_intersex,
    color_asexual,
    color_ally
};

LightHandler::LightHandler() {
    this->strip = Adafruit_NeoPixel(NUM_PIXELS, LED_PIN, NEO_GRBW + NEO_KHZ800);  // or NEO_GRBW
    this->strip.begin();
    // this->strip.setBrightness(BRIGHTNESS);

    // restore pattern and mode from eeprom
    this->brightness = 255; // storeGetBrightness();
    this->pattern = 0; // storeGetPattern();
    this->mode = 0; // storeGetMode();

    this->patternStep = 0;
    this->modeStep = 0;
    this->patternHold = 0;
    this->modeDir = 0;

    this->crossfadeAmount = getCrossfadeAmount(
        translateColor(this->strip.getPixelColor(0)),
        patterns[this->pattern][this->patternStep]);
}

LightHandler::~LightHandler() {
}

void LightHandler::step() {
    if (this->mode == MODE_BLINK) {
        this->stepModeBlink();
    } else if (this->mode == MODE_CROSSFADE_ALL ||
            this->mode == MODE_CROSSFADE_ACROSS ||
            this->mode == MODE_CROSSFADE_DOWN) {
        this->stepModeCrossfade(this->mode);
    } else if (this->mode == MODE_CHASE_AROUND ||
            this->mode == MODE_CHASE_ACROSS ||
            this->mode == MODE_CHASE_DOWN) {
        this->stepModeChase(this->mode);
    } else if (this->mode == MODE_SPARKS) {
        this->stepModeSparks();
    }
    this->strip.show();
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
                this->crossfadeAmount = getCrossfadeAmount(color, colorOff);
            } else {
                this->modeStep = 0;
                this->patternStep += 1;
                if (this->patternStep == sizeof(patterns[this->pattern]) + 1) {
                    this->patternStep = 0;
                }
                this->crossfadeAmount = getCrossfadeAmount(
                    color, patterns[this->pattern][this->patternStep]);
            }
        }
    }
}

void LightHandler::stepModeCrossfade(uint8_t variant) {
    // for crossfade, everything's the same, so no reason to step each one
    color_t target = patterns[this->pattern][this->patternStep];
    color_t color = translateColor(this->strip.getPixelColor(0));
    color = stepColor(color, target, this->crossfadeAmount);

    for (uint8_t i = 0; i < NUM_PIXELS; i += 1) {
        this->strip.setPixelColor(i, color.red, color.green, color.blue, 0);
    }

    if (isEqual(color, target)) {
        // if need to step pattern
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

void LightHandler::stepModeChase(uint8_t variant) {
    uint8_t *block, *prevBlock;

    // if (variant == MODE_CHASE_ACROSS) {
        prevBlock = cols[this->modeStep];
        this->modeStep = this->modeDir == 0 ? this->modeStep + 1 : this->modeStep - 1;
        if (this->modeStep + 1 == LED_COLS) {
            this->modeDir = 1;
        } else if (this->modeStep == 0) {
            this->modeDir = 0;
            this->patternStep += 1;
            if (this->patternStep == sizeof(patterns[this->pattern]) + 1) {
                this->patternStep = 0;
            }
        }
        block = cols[this->modeStep];
    // }

    // for (uint8_t i = 0; i < sizeof(prevBlock); i += 1) {
    //     this->strip.setPixelColor(prevBlock[i], 0, 0, 0, 0);
    // }
    for (uint8_t i = 0; i < sizeof(block); i += 1) {
        this->strip.setPixelColor(block[i],
                                  patterns[this->pattern][this->patternStep].red,
                                  patterns[this->pattern][this->patternStep].green,
                                  patterns[this->pattern][this->patternStep].blue,
                                  0);
    }


    // @TODO implement
}

void LightHandler::stepModeSparks() {
    if (this->modeStep == 1) {
        // if already on, turn off or hold
        this->strip.setPixelColor(this->patternStep, 0, 0, 0, 0);
        this->modeStep = 0;
    } else {
        if (pseudorand() % 100 < SPARK_CHANCE) {
            uint8_t idx = pseudorand() % (sizeof(patterns[this->pattern]) + 1);
            this->patternStep = pseudorand() % NUM_PIXELS;
            this->strip.setPixelColor(this->patternStep,
                                      patterns[this->pattern][idx].red,
                                      patterns[this->pattern][idx].green,
                                      patterns[this->pattern][idx].blue,
                                      0);
            this->modeStep = 1;
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
        patterns[this->pattern][this->patternStep]);

    // @TODO uncomment
    storeSetPattern(this->pattern);
}

void LightHandler::stepMode() {
    this->mode += 1;
    if (this->mode == ACTIVE_MODES) {  // loop back around
        this->mode = 0;
    }

    // reset state
    this->patternStep = 0;
    this->modeStep = 0;
    this->modeDir = 0;

    this->crossfadeAmount = getCrossfadeAmount(
        translateColor(this->strip.getPixelColor(0)),
        patterns[this->pattern][this->patternStep]);

    // @TODO uncomment
    storeSetMode(this->mode);

    this->clear();
}

void LightHandler::stepBrightness() {
  this->brightness += 1;
  if (this->brightness == BRIGHTNESS_SETTINGS) {
    this->brightness = 0;
  }
  // storeSetBrightness(this->brightness);
}

void LightHandler::clear() {
  for (uint8_t p = NUM_PIXELS; p > 0; p -= 1) {
    this->strip.setPixelColor(p, 0, 0, 0, 0);
  }
  this->strip.show();
}

// void LightHandler::debug() {
//
//     for (uint8_t p = NUM_PIXELS; p > 0; p -= 1) {
//         for (uint8_t i = 0; i < 255; i += 1) {
//             this->strip.setPixelColor(p - 1, i, i, i, 0);
//             this->strip.show();
//             delay(1);
//         }
//     }
//
//     delay(1000);
//
//     for (uint8_t i = 255; i > 0; i -= 1) {
//         for (uint8_t p = 0; p < NUM_PIXELS; p += 1) {
//             this->strip.setPixelColor(p, i - 1, i - 1, i - 1, 0);
//         }
//         this->strip.show();
//     }
// }

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
    // @TODO remove basics
    int8_t diff = current - target;

    if (diff > 0) {
        if (diff > amount) {  // increment up
            return current + amount;
        }
    } else if (-1 * diff < amount) {  // increment down
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
    // return (current > target ? current - target : target - current) / CROSSFADE_STEPS + 1;
}
