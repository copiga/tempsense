#ifndef APPSTATE_DEF
#define APPSTATE_DEF

#include <stdbool.h>
#include <stdint.h>


struct appstate
{
    int ledOn:1;
    int master:1;
    unsigned int ledColour:8;
    unsigned int probeCount:8;
    unsigned int probeID:8;
    float temp;
};
#endif
//padinfo
//32 bit word
//word aligned
