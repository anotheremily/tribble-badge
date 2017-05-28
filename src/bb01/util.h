#ifndef UTIL_H
#define UTIL_H

#include "constants.h"

#ifdef TARGET_ARDUINO
    int freeRam();
#endif

/**
 * Return semi-random number
 * @return uint8_t random number
 */
unsigned int pseudorand();

#endif
