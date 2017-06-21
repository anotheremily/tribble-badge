/**
 * EEPROM storage
 * Emily Young <emily@zavtralabs.com>
 *
 * From Arduino site:
 * An EEPROM write takes 3.3 ms to complete. The EEPROM memory has a
 * specified life of 100,000 write/erase cycles, so you may need to
 * be careful about how often you write to it.
 */

#ifndef STORE_H
#define STORE_H

#include "constants.h"

/**
 * Initialize EEPROM.
 * @param uint8_t badge id
 */
void storeInit(uint8_t);

/**
 * Get id of the last mode
 * @return mode
 */
uint8_t storeGetMode();

/**
 * Set mode
 */
void storeSetMode(uint8_t);

/**
 * Get id of the pattern
 * @return pattern
 */
uint8_t storeGetPattern();

/**
 * Store pattern
 */
void storeSetPattern(uint8_t);

/**
 * Get current brightness value
 * @return brightness (0-255)
 */
uint8_t storeGetBrightness();

/**
 * Set brightness
 */
void storeSetBrightness(uint8_t);

#endif
