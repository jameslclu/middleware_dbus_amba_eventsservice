
#ifndef _CONTROLLERMANAGER_H_
#define _CONTROLLERMANAGER_H_

#ifdef __cplusplus
extern "C" {
#endif

int mcuI2cCmdInit(void);
int mcuI2cCmdDeInit(void);
int getMcuVersion(char szIspVersion[], char szApromVersion[]);
int getBoardType(int *boardtype);
int setLed(const char szStatusLED[]);
int getLed(char szStatusLED[]);
int setSirenState(const char szState[]);
int getSirenState(char szState[]);
int setInternalHeaterState(const char szState[]);
int getInternalHeaterState(char szState[]);
int getInternalTemperature(char *tmep);
int getBatteryVoltage(int *voltage, int *cell);

#ifdef __cplusplus
}
#endif

#endif // _CONTROLLERMANAGER_H_
