#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"

#include "defines.h"
#include "led.h"

void ledSetColour(uint8_t colour)
{
	GPIOPinWrite(GPIO_PORTF_BASE, RED_LED|BLUE_LED|GREEN_LED, colour);
}
