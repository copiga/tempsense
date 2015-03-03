#ifndef MASTER_COMMANDS_DEF
#define MASTER_COMMANDS_DEF

extern int setCommand(int argc, char **argv);
extern int getCommand(int argc, char **argv);
extern int statusCommand(int argc, char **argv);
extern int ledCommand(int argc, char **argv);

extern void setTemp(float temp, int probeID);
extern void getTemp(int probeID);
extern void statusProbe(int probeID);
extern void statusAll(void);

#endif
