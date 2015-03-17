#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/rom.h"
#include "driverlib/gpio.h"
#include "led.h"

void outputOn(int output)
{
    ROM_GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2, GPIO_PIN_2);
    return;
}

void outputOff(int output)
{
    ROM_GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2, 0);
    return;
}
