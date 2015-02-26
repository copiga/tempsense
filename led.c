#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/rom.h"
#include "led.h"

void ledSetColour(uint8_t colour)
{
	ROM_GPIOPinWrite(GPIO_PORTF_BASE, RED_LED|BLUE_LED|GREEN_LED, colour);
}

void errorBlink(uint8_t colour, int rate)
{
    while(1)
    {
        ledSetColour(colour);
        ROM_SysCtlDelay(rate);
        ledSetColour(0);
        ROM_SysCtlDelay(rate);
    }
}
