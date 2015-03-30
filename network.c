#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "utils/uartstdio.h"
#include "network.h"

void sendBit(bool bit, int interface)
{
    UARTprintf("%s\t%d\n", bit?"true":"false", interface);
    
    
    disableNetInterrupts(interface);
    ROM_GPIOPinTypeGPIOOutput(interface, NET_DATA_PIN);
    ROM_GPIOPinTypeGPIOOutput(interface, NET_CLOCK_PIN);

    /*set data pin*/
    if(bit)
	GPIOPinWrite(interface, NET_DATA_PIN, 1);
    else
	GPIOPinWrite(interface, NET_DATA_PIN, 0);

    /*set clock pin*/
    GPIOPinWrite(interface, NET_CLOCK_PIN, 1);
    ROM_SysCtlDelay(NET_MIN_DELAY);
    GPIOPinWrite(interface, NET_CLOCK_PIN, 0);

    ROM_GPIOPinTypeGPIOInput(interface, NET_DATA_PIN);
    ROM_GPIOPinTypeGPIOInput(interface, NET_CLOCK_PIN);
    enableNetInterrupts(interface);
    
    return;
}

void sendByte(uint8_t byte, int interface)
{
    UARTprintf("sendByte\t%c\n", byte);
    
    /***************************/
    /* for i from 0 to 8       */
    /* 	      send byte.bit(i) */
    /* return                  */
    /***************************/
    sendBit((byte&1)?1:0, interface);
    sendBit((byte&2)?1:0, interface);
    sendBit((byte&4)?1:0, interface);
    sendBit((byte&8)?1:0, interface);
    sendBit((byte&16)?1:0, interface);
    sendBit((byte&32)?1:0, interface);
    sendBit((byte&64)?1:0, interface);
    sendBit((byte&128)?1:0, interface);

    return;
}

void enableNetInterrupts(int interface)
{
}

void disableNetInterrupts(int interface)
{
}
