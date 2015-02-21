#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"

#include "defines.h"
#include "led.h"

void ledSetColour(uint8_t colour)
{
	GPIOPinWrite(GPIO_PORTF_BASE, RED_LED|BLUE_LED|GREEN_LED, colour);
}

void errorBlink(uint8_t colour, int rate)
{
    while(1)
    {
        ledSetColour(colour);
        SysCtlDelay(rate);
        ledSetColour(0);
        SysCtlDelay(rate);
    }
}
