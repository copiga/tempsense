#ifndef LED_DEF
#define LED_DEF
#include <stdint.h>

#define RED_LED   0x00000002
#define BLUE_LED  0x00000004
#define GREEN_LED 0x00000008

extern void ledSetColour(uint8_t colour);
extern void errorBlink(uint8_t colour, int rate);
extern void ledOn(void);
extern void ledOff(void);
#endif
