/**
 * EEPROM storage
 * Emily Young <emily@zavtralabs.com>
 */

#include <EEPROM.h>
#include "store.h"

void storeInit(uint8_t badgeId) {
    storeSetPattern(0);
    storeSetMode(0);
    storeSetBrightness(0);
}

uint8_t storeGetMode() {
    return EEPROM.read(ADDRESS_MODE);
}

void storeSetMode(uint8_t mode) {
    EEPROM.write(ADDRESS_MODE, mode);
}

uint8_t storeGetPattern() {
    return EEPROM.read(ADDRESS_PATTERN);
}

void storeSetPattern(uint8_t pattern) {
    EEPROM.write(ADDRESS_PATTERN, pattern);
}

uint8_t storeGetBrightness() {
  return EEPROM.read(ADDRESS_BRIGHTNESS);
}

void storeSetBrightness(uint8_t brightness) {
  EEPROM.write(ADDRESS_BRIGHTNESS, brightness);
}
