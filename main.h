#ifndef MAIN_DEF
#define MAIN_DEF
extern void SysTickIntHandler(void);
extern void configureUART(void);
extern int bootUp(void);
extern void tests(void);
extern void maintainTemp(void);
extern void calcTemps(void);
#endif
