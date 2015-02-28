#ifndef ADC_DEF
#define ADC_DEF
extern int setupADC(void);
extern int getTempFromInternal(void);
extern int getAverageTempFromInternal(void);
extern int getTempFromExternal(void);
extern int getAverageTempFromExternal(void);
#endif
#ifndef ADC_AVERAGE_SIZE
#define ADC_AVERAGE_SIZE 10
#endif
