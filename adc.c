#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/adc.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/rom.h"

#include "adc.h"

int setupADC(void)
{
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    ADCSequenceConfigure(ADC0_BASE, 3, ADC_TRIGGER_PROCESSOR, 0);
    ADCSequenceStepConfigure(ADC0_BASE, 3, 0, ADC_CTL_TS|ADC_CTL_IE|ADC_CTL_END);
    ADCSequenceEnable(ADC0_BASE, 3);
    ADCIntClear(ADC0_BASE, 3);
    return 0;
}

int getTempFromInternal(void)
{
    uint32_t temp[1];
    ADCProcessorTrigger(ADC0_BASE, 3);
    while(!ADCIntStatus(ADC0_BASE, 3, false));
    ADCIntClear(ADC0_BASE, 3);
    ADCSequenceDataGet(ADC0_BASE, 3, temp);
    return ((1475 * 4096) - (2250 * temp[0])) / 40960; //calibration
}

int getAverageTempFromInternal(void)
{
    int temp[ADC_AVERAGE_SIZE];
    int i = 0;
    int out = 0;
    
    for(i=0;i<=ADC_AVERAGE_SIZE;i++)
	temp[i] = getTempFromInternal();
    
    for(i=0;i<=ADC_AVERAGE_SIZE;i++)
	out+=temp[i];
    out/=ADC_AVERAGE_SIZE;
    return out;
}

int getTempFromExternal(void)
{
    return 0;
}

int getAverageTempFromExternal(void)
{
    int temp[ADC_AVERAGE_SIZE];
    int i = 0;
    int out = 0;
    
    for(i=0;i<=ADC_AVERAGE_SIZE;i++)
	temp[i] = getTempFromExternal();
    
    for(i=0;i<=ADC_AVERAGE_SIZE;i++)
	out+=temp[i];
    out/=ADC_AVERAGE_SIZE;
    return out;
}
