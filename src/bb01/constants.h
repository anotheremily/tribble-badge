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

#define DEBOUNCE_DELAY 50

// Lights
#define LED_PIN 0
#define PIXELS 14
#define BRIGHTNESS 50

#define CROSSFADE_AMOUNT 10

#define CHANNEL_ON 255
#define CHANNEL_OFF 0

/**
 * Patterns
 * Pride
 * RGB
 * Trans
 * Genderqueer
 * Nonbinary
 * Intersex
 *
 * TBD Patterns
 * Bisexual
 * Pansexual
 * Asexual
 * Ally
 * Leather
 * Bear
 */
#define PATTERN_RGB         0
#define PATTERN_PRIDE       1
#define PATTERN_TRANS       2
#define PATTERN_GENDERQUEER 3
#define PATTERN_BISEXUAL    4
#define PATTERN_PANSEXUAL   5
#define PATTERN_NONBINARY   6
#define PATTERN_INTERSEX    7
#define PATTERN_ASEXUAL     8
#define PATTERN_ALLY        9
#define PATTERN_LEATHER     10
#define PATTERN_BEAR        11

#define ACTIVE_PATTERNS 6

/**
 * Modes:
 * - Blink
 * - Crossfade (All)
 * - Crossfade (Horizontal/Across)
 * - Crossfade (Vertical/Down)
 * - Chase (Circles)
 * - Sparks (Flashing Random Colors)
 * - Visualizer 1 TBD
 * - Visualizer 2 TBD
 */
#define MODE_BLINK          0
#define MODE_CROSSFADE_ALL  1
#define MODE_CROSSFADE_HORZ 2
#define MODE_CROSSFADE_VERT 3
#define MODE_CHASE          4
#define MODE_SPARKS         5
#define MODE_VIS_1          6
#define MODE_VIS_2          7

#endif
