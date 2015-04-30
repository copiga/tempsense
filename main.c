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
#include "effector.h"
#include "network.h"
#include "adc.h"
#include "appstate.h"
#include "main.h"

#define SYSTICKSS 1
#define DEFAULT_TEMP 20
#define DEFAULT_TOLERANCE 0.5
#define INPUT_LENGTH 50

struct appstate appState;

int main(void)
{
    char inputText[INPUT_LENGTH];

    bootUp();
    setupADC();
    calcTemps();
    ledSetColour(GREEN_LED);
//    while(1)ledSetColour(UARTPeek('\r')==-1?GREEN_LED:BLUE_LED);
    
    
    while(true)
    {	
	while(UARTPeek('\r') == -1)
	{
	    ROM_SysCtlDelay(ROM_SysCtlClockGet()/1000);
	}
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
    }
}

void calcTemps(void)
{
    appState.minTemp = (appState.temp - appState.tolerance)*10;
    appState.maxTemp = (appState.temp + appState.tolerance)*10;
}

void maintainTemp(void)
{
    int temp = getSafeAverageTempFromExternal();
    calcTemps();
    if(temp >= appState.maxTemp)
    {
	outputOff(0);
	ledSetColour(RED_LED);
    }
    else if(temp <= appState.minTemp)
    {
	outputOn(0);
	ledSetColour(BLUE_LED);
    }
    else
	ledSetColour(0);

    return;
}

void SysTickIntHandler(void)
{
    maintainTemp();
    return;
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
	
	/*enable effector*/
	enableEffector();

	/*enable FPU*/
	ROM_FPUEnable();
	ROM_FPUStackingEnable();
	
	/*enable LED*/
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	ROM_GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, RED_LED|BLUE_LED|GREEN_LED);
	
	/*enable output*/
	ROM_GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_2);

	/*enable network*/
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	ROM_GPIOPinTypeGPIOOutput(NET_INTERFACE_A, NET_DATA_PIN|NET_CLOCK_PIN);
	ROM_GPIOPinTypeGPIOOutput(NET_INTERFACE_B, NET_DATA_PIN|NET_CLOCK_PIN);

	
	appState.ledOn = true;
	appState.temp = DEFAULT_TEMP;
	appState.tolerance = DEFAULT_TOLERANCE;

	/*setup systick*/
	ROM_SysTickPeriodSet((ROM_SysCtlClockGet()*10) / SYSTICKSS);
	ROM_SysTickEnable();
	ROM_SysTickIntEnable();

	/*enable network interrupts*/
	enableNetInterrupts(NET_INTERFACE_A);
	enableNetInterrupts(NET_INTERFACE_B);
	
	return 0;
}
