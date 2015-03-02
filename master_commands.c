#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "utils/ustdlib.h"
#include "utils/uartstdio.h"
#include "utils/cmdline.h"

#include "led.h"
#include "adc.h"
#include "appstate.h"
#include "utils.h"
#include "master_commands.h"

extern struct appstate appState;

//global tCmdLineEntry array for the command processor, do not rename
tCmdLineEntry g_psCmdTable[]=
{
    {"get",    getCommand,    "run the get command"},
    {"set",    setCommand,    "run the set command"},
    {"status", statusCommand, "get the status"},
    {"led",    ledCommand,    "toggle the led"},
    //MUST END IN NULL
    {0,0,0}
};

int setCommand(int argc, char **argv)
{
    UARTprintf("setCommand run\n");
    return 0;
}

int getCommand(int argc, char **argv)
{
    char temp[10];
    floatString(getTempFromInternal(), temp);
    UARTprintf("temp: %sc\n", temp);
    return 0;
}

int statusCommand(int argc, char **argv)
{
    UARTprintf("ledcolour: %d\tledstatus: %s\n", appState.ledColour, (appState.ledOn)?"on":"off");
    return 0;
}

int ledCommand(int argc, char **argv)
{
    if(argc >= 2)
    {
	if(argv[1][0] == 'o' && argv[1][1] == 'n')
	    ledOn();
	else if(argv[1][0] == 'o' && argv[1][1] == 'f')
	    ledOff();
	else if(argv[1][0] == 'r')
	    ledSetColour(RED_LED);
	else if(argv[1][0] == 'g')
	    ledSetColour(GREEN_LED);
	else if(argv[1][0] == 'b')
	    ledSetColour(BLUE_LED);
    }
    return 0;
}
