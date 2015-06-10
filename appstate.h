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
    uint8_t probeID;
    float temp;
    float tolerance;
    int maxTemp;
    int minTemp;
};

#endif
//padinfo
//32 bit word
//word aligned
