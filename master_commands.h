#ifndef MASTER_COMMANDS_DEF
#define MASTER_COMMANDS_DEF

extern int setCommand(int argc, char **argv);
extern int getCommand(int argc, char **argv);
extern int statusCommand(int argc, char **argv);
extern int ledCommand(int argc, char **argv);
extern int sendCommand(int argc, char **argv);

extern void setTemp(int probeID, float temp);
extern void getTemp(int probeID);
extern void statusProbe(int probeID);
extern void statusAll(void);

#endif
