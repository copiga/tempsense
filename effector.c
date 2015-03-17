#include "gpio.h"
#include "led.h"

void outputOn(int output)
{
    ROM_GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_7, 1);
    ledSetColour(BLUE_LED);
    return;
}

void outputOff(int output)
{
    ROM_GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_7, 0);
    ledSetColour(RED_LED);
    return;
}
