
#ifndef _ORYXSTORAGEMANAGER_H_
#define _ORYXSTORAGEMANAGER_H_

#include "StorageManager.h"

enum format_status {
  STORAGE_FORMAT_IDLE = 0,
  STORAGE_FORMAT_BUSY,
};

int oryxStorageManagerInit(void);
int oryxStorageManagerDeinit(void);
int oryxStorageMonitorFreeSpaceStart(std::string const& directory, int const& free_space);
int oryxStorageMonitorFreeSpaceStop(void);
bool oryxStorageMonitorFreeSpaceState(void);
int oryxStorageFormatSDCard(std::string const& mmcblk_dev, std::string const& mount_point);
int oryxStorageGetSDCardStatus(std::string const& mmcblk_dev, struct storage_state& state);
int oryxStorageGetFormatStatus(void);

#endif // _ORYXSTORAGEMANAGER_H_
