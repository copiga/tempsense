#ifndef APPSTATE_DEF
#define APPSTATE_DEF

#include <stdbool.h>
#include <stdint.h>

struct appstate
{
    bool ledOn;
    uint8_t ledColour;
    uint8_t probeCount;
};
#endif
