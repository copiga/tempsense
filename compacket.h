#ifndef COMPACKET_DEF
#define COMPACKET_DEF
//#define READWRITE 01
//#define ADDRESS 02
//#define TEMP 32
#include <stdbool.h>
#include <stdint.h>

struct compacket
{
    unsigned int write; // read is 0, write is 1
    uint8_t address; // specify probe address
    uint8_t temp; // specify temperature to set / return
    uint8_t status; // status indication to return when requested
};

#endif
//padinfo
//32 bit word
//word aligned
