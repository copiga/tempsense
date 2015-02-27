#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/rom.h"
#include "led.h"
#include "appstate.h"

extern struct appstate appState;

void ledSetColour(uint8_t colour)
{
    if(appState.ledOn == true)
    {
	ROM_GPIOPinWrite(GPIO_PORTF_BASE, RED_LED|BLUE_LED|GREEN_LED, colour);
    }
    appState.ledColour = colour;
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

void ledOn(void)
{
    appState.ledOn = true;
    ledSetColour(appState.ledColour);    
}

void ledOff(void)
{
    appState.ledOn = false;
    ROM_GPIOPinWrite(GPIO_PORTF_BASE, RED_LED|BLUE_LED|GREEN_LED, 0);
}
