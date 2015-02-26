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
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "utils/cmdline.h"

#include "led.h"
#include "adc.h"
#include "main.h"

#define INPUT_LENGTH 50

int main(void)
{
    char inputText[INPUT_LENGTH];
    
    bootUp();
    setupADC();
    ledSetColour(GREEN_LED);
    
  j:
    while(UARTPeek('\r') == -1)
	ROM_SysCtlDelay(ROM_SysCtlClockGet()/1000);
    UARTgets(inputText, INPUT_LENGTH);
    switch(CmdLineProcess(inputText))
    {
	case CMDLINE_BAD_CMD:
	    UARTprintf("bad command\n");
	    break;
	case CMDLINE_TOO_MANY_ARGS:
	    UARTprintf("too many args\n");
	    break;
	case CMDLINE_TOO_FEW_ARGS:
	    UARTprintf("too few args");
	    break;
	case CMDLINE_INVALID_ARG:
	    UARTprintf("invalid arg\n");
	    break;
    }
    goto j;
}

void SysTickIntHandler(void)
{
	/*do nothing, return nothing*/
}

void configureUART(void)
{
    //
    // Enable the GPIO Peripheral used by the UART.
    //
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    //
    // Enable UART0
    //
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    //
    // Configure GPIO Pins for UART mode.
    //
    ROM_GPIOPinConfigure(GPIO_PA0_U0RX);
    ROM_GPIOPinConfigure(GPIO_PA1_U0TX);
    ROM_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    //
    // Use the internal 16MHz oscillator as the UART clock source.
    //
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);

    //
    // Initialize the UART for console I/O.
    //
    UARTStdioConfig(0, 115200, 16000000);
}

int bootUp(void)
{
	/*set clock to 20MHz*/
	ROM_SysCtlClockSet(SYSCTL_SYSDIV_10 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);

	/*enable UART*/
	configureUART();

	/*enable LED*/
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	ROM_GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, RED_LED|BLUE_LED|GREEN_LED);
	return 0;
}

