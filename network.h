#ifndef NETWORK_DEF
#define NETWORK_DEF

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"

#define NET_DATA_PIN GPIO_PIN_6
#define NET_CLOCK_PIN GPIO_PIN_7

#define NET_MIN_DELAY ROM_SysCtlClockGet()/1000

#define NET_INTERFACE_A GPIO_PORTD_BASE
#define NET_INTERFACE_B GPIO_PORTC_BASE

void sendBit(bool bit, int interface);
void sendByte(uint8_t bit, int interface);
void enableNetInterrupts(int interface);
void disableNetInterrupts(int interface);


#endif
