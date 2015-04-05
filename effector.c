#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/rom.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "led.h"

void enableEffector(void)
{
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    ROM_GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_2);
}
    

void outputOn(int output)
{
    ROM_GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2, GPIO_PIN_2);
    return;
}

void outputOff(int output)
{
    ROM_GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2, 0);
    return;
}
