#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "utils/ustdlib.h"
#include "utils/uartstdio.h"
#include "utils/cmdline.h"

#include "led.h"
#include "master_commands.h"

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
    UARTprintf("getCommand run\n");
    return 0;
}

int statusCommand(int argc, char **argv)
{
    UARTprintf("statusCommand run\n");
    return 0;
}

int ledCommand(int argc, char **argv)
{
    if(argc >= 2)
    {
	if(argv[1][1] == 'n')
	    ledOn();
	else
	    ledOff();
    }
    return 0;
}
