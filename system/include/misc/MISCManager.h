
#ifndef _MISCMANAGER_H_
#define _MISCMANAGER_H_

#include "SystemCommon.h"

#ifdef __cplusplus
extern "C" {
#endif

#define PIR_FILE_DEVICE "/proc/pir"  /* Char device driver file. */

int getTotalInternalFlashVolume(char szTotalVolume[]);
int getFreeInternalFlashVolume(char szAvailableVolume[]);
int getSerialNumber(char szSerialNo[]);
int getHostName(char szDeviceName[]);
int setHostName(const char szDeviceName[]);
int getTimeZone(char szTimeZone[]);
int setTimeZone(const char szTimeZone[]);
int getTime(char szTime[]);
int setTime(const char szTime[]);
int getVersion(char szVersion[]);
int doSystemReboot(void);
int doFactoryReset(const char szSha1sum[]);
int getNtpState(char szState[]);
int setNtpState(const char szState[]);
int getPIRSensitivity(int *pPIRSensitivity);
int setPIRSensitivity(const int PIRSensitivity);
int getChimeType(int *pType);
int setChimeType(const int Type);
int getLightSensorLevel(int *pLevel);
int getBoardVersion(char szBoardVersion[]);

int runHardwareInfoScript(void);
int PIRThreadStart(void);
int PIRThreadStop(void);
int lightSensorThreadStart(void);
int lightSensorThreadStop(void);

#ifdef __cplusplus
}
#endif

#endif // _MISCMANAGER_H_
