#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
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
    if(argc == 4)
    {
	float temp;

	stringFloat(argv[3], &temp);
	
	if(strcmp(argv[1], "temp")==0)
	    setTemp(atoi(argv[2]), temp);
	else
	    UARTprintf("invalid command\n");
    }
    else
	UARTprintf("ERROR WITH SET\n");
    
    return 0;
}

int getCommand(int argc, char **argv)
{
    if(argc == 3)
    {
	if(strcmp(argv[1], "temp")==0)
	    getTemp(atoi(argv[2]));
	else
	    UARTprintf("invalid command\n");
    }
    else
	UARTprintf("ERROR WITH GET\n");
    return 0;
}

int statusCommand(int argc, char **argv)
{
    statusAll();
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

void setTemp(int probeID, float temp)
{
    if(probeID == 0)
	appState.temp = temp;
}

void getTemp(int probeID)
{
    char temp[10];

    if(probeID == 0)
	floatString(getAverageTempFromInternal(), temp);
    else if(probeID == 1)
	floatString(getAverageTempFromExternal(), temp);
    else
	strcpy(temp, "NOT DONE");
    UARTprintf("%s\n", temp);
}

void statusProbe(int probeID)
{
}

void statusAll(void)
{
    UARTprintf("ledcolour: %d\tledstatus: %s\tprobeCount: %d\n", appState.ledColour, (appState.ledOn)?"on":"off", appState.probeCount);
}
