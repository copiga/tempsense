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
    ADCSequenceStepConfigure(ADC0_BASE, 3, 0, ADC_CTL_CH6|ADC_CTL_IE|ADC_CTL_END);
    ADCSequenceEnable(ADC0_BASE, 3);
    ADCIntClear(ADC0_BASE, 3);

    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC1);
    ADCSequenceConfigure(ADC1_BASE, 3, ADC_TRIGGER_PROCESSOR, 0);
    ADCSequenceStepConfigure(ADC1_BASE, 3, 0, ADC_CTL_CH7|ADC_CTL_IE|ADC_CTL_END);
    ADCSequenceEnable(ADC1_BASE, 3);
    ADCIntClear(ADC1_BASE, 3);
    return 0;
}

float getLightLevel(void)
{
    uint32_t light[1];
    ADCProcessorTrigger(ADC0_BASE, 3);
    while(!ADCIntStatus(ADC0_BASE, 3, false));
    ADCIntClear(ADC0_BASE, 3);
    ADCSequenceDataGet(ADC0_BASE, 3, light);
    return light[0];//calibration
}

float getAverageLightLevel(void)
{
    int light[ADC_AVERAGE_SIZE];
    int i = 0;
    int out = 0;
    
    for(i=0;i<=ADC_AVERAGE_SIZE;i++)
	light[i] = getLightLevel();    
    for(i=0;i<=ADC_AVERAGE_SIZE;i++)
	out+=light[i];
    out/=ADC_AVERAGE_SIZE;
    return out;
}

float getTempFromExternal(void)
{
    uint32_t temp[1];
    double millivolts;
    ADCProcessorTrigger(ADC1_BASE, 3);
    while(!ADCIntStatus(ADC1_BASE, 3, false));
    ADCIntClear(ADC1_BASE, 3);
    ADCSequenceDataGet(ADC1_BASE, 3, temp);
#ifdef LM35TEMPSENSOR
    return temp[0]*(3.3/4096)/0.01;
#elif LMT86TEMPSENSOR
    millivolts = temp[0]*(330000/4096);
    return millivolts/-109;
#else
    return temp[0];
#endif
    /*temperature = reading*(vref/2^ADCwidth)/stepPerDegree*/
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

int getSafeAverageTempFromExternal(void)
{
    int temp;
    temp = getAverageTempFromExternal() * 10;
    return temp;
}
