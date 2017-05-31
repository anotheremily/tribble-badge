/**
 * Constants
 * Emily Young <emily@zavtralabs.com>
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H

#define TARGET_TRINKET
// #define TARGET_ARDUINO  // for debugging with serial

// Loop Constants
#define LOOP_DELAY 100  // ms

#define RAND_SEED 123456789
#define RAND_A 1103515245
#define RAND_C 12345
#define RAND_M 2554294967296   // 2^32

// Buttons
#define BUTTON_NONE 0
#define BUTTON_1 1
#define BUTTON_2 2
#define BUTTON_1_2 3

#define BUTTON_1_PIN 2
#define BUTTON_2_PIN 3

#define BUTTON_OFF LOW
#define BUTTON_ON HIGH

#define DEBOUNCE_DELAY 40

// Pairing & Memory
#define NUM_BADGES 60
#define UNLOCK_FEATURES 5

#define ADDRESS_BADGE_ID 0
#define ADDRESS_LEVEL 1
#define ADDRESS_PAIRING_COUNT  2
#define ADDRESS_LAST_MODE 3
#define ADDRESS_LAST_PATTERN 4

#define ADDRESS_UNLOCK_START  10

#define ADDRESS_PAIRING_START  100

// Lights
#define LED_PIN 0
#define NUM_PIXELS 14
#define BRIGHTNESS 255

#define CROSSFADE_AMOUNT_SLOW 10
#define CROSSFADE_AMOUNT_FAST 10
#define CROSSFADE_STEPS 40
#define CROSSFADE_HOLD 20

#define CHANNEL_ON 255
#define CHANNEL_OFF 0

// Row, column definitions
//     0   1   2   3   4   5
//     ----------------------
// 0       03          10
// 1   04      02  11      09
// 2       05          13
// 3   05      01  12      08
// 4       00          07
#define LED_ROWS 5
#define LED_COLS 6

// Patterns
#define ACTIVE_PATTERNS 6  // 12

#define PATTERN_RGB     0
#define PATTERN_PRIDE    1
#define PATTERN_TRANS    2
#define PATTERN_GENDERQUEER 3
#define PATTERN_BISEXUAL  4
#define PATTERN_PANSEXUAL  5

// Not implemented yet
#define PATTERN_NONBINARY  6
#define PATTERN_INTERSEX  7
#define PATTERN_ASEXUAL   8
#define PATTERN_ALLY    9
#define PATTERN_LEATHER   10
#define PATTERN_BEAR    11

// Modes
#define ACTIVE_MODES 3  // 8

#define MODE_CHASE_ACROSS 3
#define MODE_SPARKS 0
#define MODE_BLINK 1
#define MODE_CROSSFADE_ALL 2

// Not implemented yet
#define MODE_CROSSFADE_ACROSS 10
#define MODE_CROSSFADE_DOWN 11
#define MODE_CHASE_AROUND 12
#define MODE_CHASE_ACROSS 13
#define MODE_CHASE_DOWN 14
#define MODE_DANCE 16
#define MODE_EQUALIZER 17

// Mode specific constants
#define SPARK_CHANCE 30  // chance of a spark firing - out of 255


#endif
