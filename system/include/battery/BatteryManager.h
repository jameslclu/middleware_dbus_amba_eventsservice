
#ifndef _BATTERYMANAGER_H_
#define _BATTERYMANAGER_H_

//Doorbell 2cell for poc
#define BATTERY_FULL_VOLTAGE            8300 //mV
#define BATTERY_LOW_VOLTAGE             7200 //mV
#define BATTERY_CRITICAL_LOW_VOLTAGE    6800 //mV

int getBattVol(int &voltage);
int getBattCap(int &capacity);

#endif /* _BATTERYMANAGER_H_ */
