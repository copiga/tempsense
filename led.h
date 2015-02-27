#ifndef LED_DEF
#define LED_DEF
#include <stdint.h>

#define RED_LED   0x00000002
#define BLUE_LED  0x00000004
#define GREEN_LED 0x00000008

void ledSetColour(uint8_t colour);
void errorBlink(uint8_t colour, int rate);
void ledOn(void);
void ledOff(void);
#endif
