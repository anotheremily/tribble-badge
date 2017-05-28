/**
 * EEPROM storage
 * Emily Young <emily@zavtralabs.com>
 */

#include <EEPROM.h>
#include "store.h"

void storeInit(uint8_t badgeId) {
    EEPROM.write(ADDRESS_BADGE_ID, badgeId);
    EEPROM.write(ADDRESS_LEVEL, 0);
    EEPROM.write(ADDRESS_PAIRING_COUNT, 0);

    for (uint8_t i = 0; i < UNLOCK_FEATURES; i += 1) {
        EEPROM.write(ADDRESS_UNLOCK_START + i, 0);
    }

    for (uint8_t i = 0; i < NUM_BADGES; i += 1) {
        EEPROM.write(ADDRESS_PAIRING_START + i, 0);
    }

    setPattern(0);
    setMode(0);
}

uint8_t getBadgeId() {
    return EEPROM.read(ADDRESS_BADGE_ID);
}

uint8_t getLevel() {
    return EEPROM.read(ADDRESS_BADGE_ID);
}

uint8_t incrLevel() {
    uint8_t level = EEPROM.read(ADDRESS_LEVEL) + 1;
    EEPROM.write(ADDRESS_LEVEL, level);
    return level;
}

uint8_t incrPairingCount() {
    uint8_t level = EEPROM.read(ADDRESS_PAIRING_COUNT) + 1;
    EEPROM.write(ADDRESS_PAIRING_COUNT, level);
    return level;
}

uint8_t getMode() {
    return EEPROM.read(ADDRESS_LAST_MODE);
}

void setMode(uint8_t mode) {
    EEPROM.write(ADDRESS_LAST_MODE, mode);
}

uint8_t getPattern() {
    return EEPROM.read(ADDRESS_LAST_PATTERN);
}

void setPattern(uint8_t pattern) {
    EEPROM.write(ADDRESS_LAST_PATTERN, pattern);
}

bool isUnlocked(uint8_t featureId) {
    return featureId < UNLOCK_FEATURES &&
        EEPROM.read(ADDRESS_UNLOCK_START + featureId) ? true : false;
}

bool isPaired(uint8_t extBadgeId) {
    return extBadgeId < NUM_BADGES &&
        EEPROM.read(ADDRESS_PAIRING_START + extBadgeId) ? true : false;
}

bool setPaired(uint8_t extBadgeId) {
    if (extBadgeId >= NUM_BADGES) {
        return false;
    }
    EEPROM.write(ADDRESS_PAIRING_START + extBadgeId, 1);
    return true;
}
