#include "util.h"

#ifdef TARGET_ARDUINO
    int freeRam () {
        extern int __heap_start, *__brkval;
        int v;
        return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
    }
#endif

// https://stackoverflow.com/questions/9492581
unsigned int pseudorand() {
    static unsigned int seed = RAND_SEED;
    seed = (RAND_A * seed + RAND_C) % RAND_M;
    return seed % 255;
}
