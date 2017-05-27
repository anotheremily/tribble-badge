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
 * Get id of the badge
 * @return badge id
 */
uint8_t getBadgeId();

/**
 * Get id of the level
 * @return level
 */
uint8_t getLevel();

/**
 * Increase level by 1
 * @return level
 */
uint8_t incrLevel();

/**
 * Get pairing count of the badge
 * @return pairing count
 */
uint8_t getPairingCount();

/**
 * Increase pairing count by 1
 * @return pairing count
 */
uint8_t incrPairingCount();

/**
 * Check if feature i is unlocked
 * @param uint8_t feature id
 * @return bool is unlocked
 */
bool isUnlocked(uint8_t);

/**
 * Check if badge is paired with connected badge
 * @param uint8_t ext badge id
 * @return bool is paired
 */
bool isPaired(uint8_t);

/**
 * Sets pairing
 * @param uint8_t ext badge id
 * @return bool is paired
 */
bool setPaired(uint8_t);

#endif
