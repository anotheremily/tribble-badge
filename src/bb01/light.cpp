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

const uint8_t col_6[] = {2, 1};
const uint8_t col_5[] = {3, 6, 0};
const uint8_t col_4[] = {4, 5};

const uint8_t col_1[] = {11, 12};
const uint8_t col_2[] = {10, 13, 7};
const uint8_t col_3[] = {9, 8};

const uint8_t *cols[] = {col_1, col_2, col_3, col_4, col_5, col_6};
const uint8_t col_length[] = {2, 3, 2, 2, 3, 2};

const color_t black        = {  0,   0,   0};
const color_t white        = {127, 127, 127};  // {255, 255, 255};
const color_t red          = {127,   0,   0};  // {255,   0,   0};
const color_t blue         = {  0,   0, 127};  // {  0,   0, 255};
const color_t green        = {  0, 127,   0};  // {  0, 255,  0};
const color_t orange       = {127,  17,   0};  // {255, 35,   0};
const color_t yellow       = {127,  60,   0};  // {255, 120,   0};
const color_t purple       = {100,   0,  50};  // {200,  0, 100};
const color_t light_blue   = { 45, 103, 125};  // { 91, 206, 250};
const color_t pink         = {127,  20,  30};  // {255,  40, 60};
// const color_t light_purple = {119,   0, 137};

const color_t color_pride[]       = {red, orange, yellow, green, blue, purple};
const color_t color_trans[]       = {light_blue, pink, white, pink};
const color_t color_genderqueer[] = {purple, white, green};  // swap light purple for purple
const color_t color_genderfluid[] = {pink, white, purple, blue};
const color_t color_bisexual[]    = {pink, purple, blue};
const color_t color_pansexual[]   = {pink, yellow, light_blue};
const color_t color_nonbinary[]   = {yellow, white, purple};
const color_t color_intersex[]    = {purple, white, light_blue, pink, white};
const color_t color_asexual[]     = {white, purple};

const color_t *patterns[] = {
    color_trans,
    color_pride,
    color_genderqueer,
    color_genderfluid,
    color_bisexual,
    color_pansexual,
    color_nonbinary,
    color_intersex,
    color_asexual};

const uint8_t pattern_length[] = {4,   // trans
                                  6,   // pride
                                  3,   // genderqueer
                                  4,   // genderfluid
                                  3,   // bisexual
                                  3,   // pansexual
                                  3,   // nonbinary
                                  5,   // intersex
                                  2};  // asexual

LightHandler::LightHandler() {
    this->strip = new Adafruit_NeoPixel(NUM_PIXELS, LED_PIN, NEO_GRBW + NEO_KHZ800);  // or NEO_GRBW
    this->strip->begin();
    // this->strip->setBrightness(BRIGHTNESS);

    // restore pattern and mode from eeprom
    this->brightness = storeGetBrightness();
    this->pattern = storeGetPattern();
    this->mode = storeGetMode();

    this->patternStep = 0;
    this->modeStep = 0;
    this->patternHold = 0;
    this->modeDir = 0;

    this->crossfadeAmount = getCrossfadeAmount(
        translateColor(this->strip->getPixelColor(0)),
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
    this->strip->show();
}

void LightHandler::stepModeBlink() {
    // get common color and target goals
    color_t target = (this->modeStep == 1)
        ? black
        : patterns[this->pattern][this->patternStep];

    color_t color = stepColor(
        translateColor(this->strip->getPixelColor(0)),
        target, this->crossfadeAmount);

    for (uint8_t i = 0; i < NUM_PIXELS; i += 1) {
        this->strip->setPixelColor(i, color.red, color.green, color.blue, 0);
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
                this->crossfadeAmount = getCrossfadeAmount(color, black);
            } else {
                this->modeStep = 0;
                this->patternStep += 1;
                if (this->patternStep == pattern_length[this->pattern]) {
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
    color_t color = translateColor(this->strip->getPixelColor(0));
    color = stepColor(color, target, this->crossfadeAmount);

    for (uint8_t i = 0; i < NUM_PIXELS; i += 1) {
        this->strip->setPixelColor(i, color.red, color.green, color.blue, 0);
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
            if (this->patternStep == pattern_length[this->pattern]) {
                this->patternStep = 0;
            }
            this->crossfadeAmount = getCrossfadeAmount(
                color, patterns[this->pattern][this->patternStep]);
        }
    }
}

void LightHandler::stepModeChase(uint8_t variant) {
    // uint8_t *block, *prevBlock;

    if (this->patternHold < CHASE_HOLD) {
        this->patternHold += 1;
    } else {
        this->patternHold = 0;

        for (uint8_t i = 0; i < col_length[this->modeStep]; i += 1) {
            this->strip->setPixelColor(cols[this->modeStep][i], 0, 0, 0, 0);
        }

        // prevBlock = cols[this->modeStep];
        this->modeStep = this->modeDir == 0 ? this->modeStep + 1 : this->modeStep - 1;
        if (this->modeStep + 1 == LED_COLS) {
            this->modeDir = 1;
        } else if (this->modeStep == 0) {
            this->modeDir = 0;
            this->patternStep += 1;
            if (this->patternStep == pattern_length[this->pattern]) {
                this->patternStep = 0;
            }
        }
        // block = cols[this->modeStep];
        // }


        for (uint8_t i = 0; i < col_length[this->modeStep]; i += 1) {
            this->strip->setPixelColor(cols[this->modeStep][i],
                                      patterns[this->pattern][this->patternStep].red,
                                      patterns[this->pattern][this->patternStep].green,
                                      patterns[this->pattern][this->patternStep].blue,
                                      0);
        }
    }

    // @TODO implement
}

void LightHandler::stepModeSparks() {
    if (this->modeStep == 1) {
        // if already on, turn off or hold
        this->strip->setPixelColor(this->patternStep, 0, 0, 0, 0);
        this->modeStep = 0;
    } else {
        if (pseudorand() % 100 < SPARK_CHANCE) {
            uint8_t idx = pseudorand() % pattern_length[this->pattern];
            this->patternStep = pseudorand() % NUM_PIXELS;
            this->strip->setPixelColor(this->patternStep,
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
        translateColor(this->strip->getPixelColor(0)),
        patterns[this->pattern][this->patternStep]);

    storeSetPattern(this->pattern);
    this->strip->clear();
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
        translateColor(this->strip->getPixelColor(0)),
        patterns[this->pattern][this->patternStep]);

    storeSetMode(this->mode);
    this->strip->clear();
}

void LightHandler::stepBrightness() {
    this->brightness += 1;
    if (this->brightness == BRIGHTNESS_SETTINGS) {
      this->brightness = 0;
    }
    storeSetBrightness(this->brightness);
}

// void LightHandler::debug() {
//
//     for (uint8_t p = NUM_PIXELS; p > 0; p -= 1) {
//         for (uint8_t i = 0; i < 255; i += 1) {
//             this->strip->setPixelColor(p - 1, i, i, i, 0);
//             this->strip->show();
//             delay(1);
//         }
//     }
//
//     delay(1000);
//
//     for (uint8_t i = 255; i > 0; i -= 1) {
//         for (uint8_t p = 0; p < NUM_PIXELS; p += 1) {
//             this->strip->setPixelColor(p, i - 1, i - 1, i - 1, 0);
//         }
//         this->strip->show();
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
    // return abs(current - target) / CROSSFADE_STEPS + 1;
    return ((current > target ? current - target : target - current) / CROSSFADE_STEPS + 1); // / (this->brightness / MAX_BRIGHTNESS) + 1;
}
