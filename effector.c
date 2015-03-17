#include "led.h"

void outputOn(int output)
{
    ledSetColour(BLUE_LED);
    return;
}

void outputOff(int output)
{
    ledSetColour(RED_LED);
    return;
}
