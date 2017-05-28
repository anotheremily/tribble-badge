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

// Buttons
#define BUTTON_NONE 0
#define BUTTON_1 1
#define BUTTON_2 2
#define BUTTON_1_2 3

#define BUTTON_1_PIN 2
#define BUTTON_2_PIN 3

#define BUTTON_OFF 0
#define BUTTON_ON 1

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

#define ROW_1 [3, 10]
#define ROW_2 [4, 2, 11, 9]
#define ROW_3 [5, 13]
#define ROW_4 [5, 1, 12, 8]
#define ROW_5 [0, 7]

#define COL_1 [4, 5]
#define COL_2 [3, 5, 0]
#define COL_3 [2, 1]
#define COL_4 [11, 12]
#define COL_5 [10, 13, 7]
#define COL_6 [9, 8]

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
#define ACTIVE_MODES 2  // 8

#define MODE_BLINK     0
#define MODE_CROSSFADE_ALL 1

// Not implemented yet
#define MODE_CROSSFADE_HORZ 2
#define MODE_CROSSFADE_VERT 3
#define MODE_CHASE 4
#define MODE_CHASE_ACROSS 5
#define MODE_CHASE_DOWN 6
#define MODE_SPARKS 7
#define MODE_DANCE 8
#define MODE_EQUALIZER 9

#endif
