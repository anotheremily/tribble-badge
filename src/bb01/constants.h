/**
 * Constants
 * Emily Young <emily@zavtralabs.com>
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H

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
#define PIXELS 14
#define BRIGHTNESS 40

#define CROSSFADE_AMOUNT 10
#define BLAH 10

#define CHANNEL_ON 255
#define CHANNEL_OFF 0

// Patterns
#define ACTIVE_PATTERNS 6

#define PATTERN_RGB     0
#define PATTERN_PRIDE    1
#define PATTERN_TRANS    2
#define PATTERN_GENDERQUEER 3
#define PATTERN_BISEXUAL  4
#define PATTERN_PANSEXUAL  5
#define PATTERN_NONBINARY  6
#define PATTERN_INTERSEX  7
#define PATTERN_ASEXUAL   8
#define PATTERN_ALLY    9
#define PATTERN_LEATHER   10
#define PATTERN_BEAR    11

// Modes
#define MODE_BLINK     0
#define MODE_CROSSFADE_ALL 1
#define MODE_CROSSFADE_HORZ 2
#define MODE_CROSSFADE_VERT 3
#define MODE_CHASE 4
#define MODE_SPARKS 5
#define MODE_DANCE 6
#define MODE_EQUALIZER 7

#define ACTIVE_MODES 2 // 8

//     0   1   2   3   4   5
//     ----------------------
// 0       03          10
// 1   04      02  11      09
// 2       05          13
// 3   05      01  12      08
// 4       00          09


#endif
