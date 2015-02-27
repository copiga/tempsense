#ifndef ADC_DEF
#define ADC_DEF
int setupADC(void);
int getTempFromInternal(void);
int getAverageTempFromInternal(void);
#endif
#ifndef ADC_AVERAGE_SIZE
#define ADC_AVERAGE_SIZE 10
#endif
