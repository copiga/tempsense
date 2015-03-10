#ifndef APPSTATE_DEF
#define APPSTATE_DEF

#include <stdbool.h>
#include <stdint.h>

struct appstate
{
    bool ledOn;
    bool master;
    uint8_t ledColour;
    uint8_t probeCount;
    float temp;
    float tolerance;
};

#endif
//padinfo
//32 bit word
//word aligned
