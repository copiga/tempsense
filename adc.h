#ifndef ADC_DEF
#define ADC_DEF
extern int setupADC(void);
extern float getLightLevel(void);
extern float getAverageLightLevel(void);
extern float getTempFromExternal(void);
extern float getAverageTempFromExternal(void);
extern int getSafeAverageTempFromExternal(void);
#endif
#ifndef ADC_AVERAGE_SIZE
#define ADC_AVERAGE_SIZE 100
#endif
