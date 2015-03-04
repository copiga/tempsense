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

    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC1);
    ADCSequenceConfigure(ADC1_BASE, 3, ADC_TRIGGER_PROCESSOR, 0);
    ADCSequenceStepConfigure(ADC1_BASE, 3, 0, ADC_CTL_CH0|ADC_CTL_IE|ADC_CTL_END);
    ADCSequenceEnable(ADC1_BASE, 3);
    ADCIntClear(ADC1_BASE, 3);
    return 0;
}

float getTempFromInternal(void)
{
    uint32_t temp[1];
    ADCProcessorTrigger(ADC0_BASE, 3);
    while(!ADCIntStatus(ADC0_BASE, 3, false));
    ADCIntClear(ADC0_BASE, 3);
    ADCSequenceDataGet(ADC0_BASE, 3, temp);
    return (1475-((2475 * temp[0]))/4096)/10;//calibration
}

float getAverageTempFromInternal(void)
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

float getTempFromExternal(void)
{
    uint32_t temp[1];
    ADCProcessorTrigger(ADC1_BASE, 3);
    while(!ADCIntStatus(ADC1_BASE, 3, false));
    ADCIntClear(ADC1_BASE, 3);
    ADCSequenceDataGet(ADC1_BASE, 3, temp);
    return temp[0]*(3.3/4096)/0.01;
    /*temperature = reading*(vref/s^ADCwidth)/stepperdegree*/
}

float getAverageTempFromExternal(void)
{
    float temp[ADC_AVERAGE_SIZE];
    int i = 0;
    float out = 0;
    
    for(i=0;i<=ADC_AVERAGE_SIZE;i++)
	temp[i] = getTempFromExternal();
    
    for(i=0;i<=ADC_AVERAGE_SIZE;i++)
	out+=temp[i];
    out/=ADC_AVERAGE_SIZE;
    return out;
}
