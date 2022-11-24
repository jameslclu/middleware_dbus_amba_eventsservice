
#ifndef _STORAGEMANAGER_H_
#define _STORAGEMANAGER_H_

#include "SystemCommon.h"

/*! @enum AM_FS_TYPE
 *  @brief defines filesystem type.
 */
enum FS_TYPE {
  FS_AUTO   = 0x00, //!< Auto detection within below types
  FS_VFAT   = 0x01, //!< Vfat filesystem
  FS_EXFAT  = 0x02, //!< Exfat filesystem
  FS_UBIFS  = 0x03, //!< Ubifs filesystem
  FS_EXT4   = 0X04, //!< Ext4 filesystem
  FS_CRYPTO_LUKS = 0X05, //!< crypto_LUKS filesystem
};

/*
 *  Defines the storage state parameters.
 */
struct storage_state {
    //! Whether the storage is mounted or not
    bool mounted = false;
    //! The device node path
    std::string device_path = "";
    //! The device mount path
    std::string mnt_point = "";
    //! The total size of the storage
    int32_t total_size_mb = 0;
    //! The free space of the storage
    int32_t available_size_mb = 0;
    //! The filesyste type of the storage
    enum FS_TYPE fstype;
};

int StorageManagerInit(void);
int StorageManagerDeinit(void);
int StorageManagerMonitorFreeSpaceStart(void);
int StorageManagerMonitorFreeSpaceStop(void);
bool StorageManagerMonitorFreeSpaceState(void);

int formatSDCard(const char szValue[]);
int getFileList(char szList[]);
int setResponseWhenFull(const char szResponseMode[]);
int getResponseWhenFull(char szResponseMode[]);
int getCryptoLuksKey(char szCryptoLuksKey[]);
int getSDcardStatus(struct storage_state& state);

#endif // _STORAGEMANAGER_H_
