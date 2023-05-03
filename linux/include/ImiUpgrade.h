/**************************************************************************
  Copyright (c) 2016 Huajie IMI Technology Co.,Ltd.
  All rights reserved.

  @file   ImiUpgrade.h
  @brief  Imi upgrade header.

  @date    2016-11-08
  @author  liwei
  @version 0.1.0

  History:
  1. 2016-11-08, liwei The initial version
**************************************************************************/

#ifndef _IMI_UPGRADE_H_
#define _IMI_UPGRADE_H_

#include <ImiPlatform.h>
#include <ImiDefines.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_ADDRESSS_LEGTH 256
typedef enum {
	
	IMI_DOWNLOAD_START = 0,
	IMI_DOWNLOADING = 1,
	IMI_DOWNLOAD_SUCCESS = 2,
	IMI_DOWNLOAD_FAILED = 3,

	IMI_UPGRADE_START = 4,

	IMI_UPLOADBLOCK_START = 5,
	IMI_UPLOADBLOCK_UPLOADING = 6,
	IMI_UPLOADBLOCK_SUCCESS = 7,
	IMI_UPLOADBLOCK_FAILED = 8,

	IMI_CHECK_START = 9,
	IMI_CHECK_CHECKING = 10,
	IMI_CHECK_SUCCESS = 11,
	IMI_CHECK_FAILED = 12,

	IMI_UPGRADE_SUCCESS = 13,
	IMI_UPGRADE_SUCCESS_NEED_REBOOT = 14,
	IMI_UPGRADE_FAILED = 15,

}IMI_UPGRADE_PROMPT;

typedef enum {
	IMI_UPGRADEERR_VERSION_NOT_CORRECT = -11,
	IMI_UPGRADEERR_SN_NOT_CORRECT = -10,
	IMI_UPGRADEERR_NOT_CONNECT_NET   = -9,
	IMI_UPGRADEERR_NOT_SUPPORT   = -8,
	IMI_UPGRADEERR_NOT_FOUND   = -6,
	IMI_UPGRADEERR_NOT_OPEN   = -5,
	IMI_UPGRADEERR_CHECK_UPGRADEINFO_FAILED = -4,
	IMI_UPGRADEERR_NO_NEED_UPGRADE = -3,
	IMI_UPGRADEERR_DEVICE_UPGRADE_DISABLED = -2,
	IMI_UPGRADEERR_NOT_INIT   = -1,

	IMI_UPGRADEERR_OK = 0,
	IMI_UPGRADEERR_DOWNLOAD_FAILED = 1,
	IMI_UPGRADEERR_PACKAGE_NOT_EXIST = 2,
	IMI_UPGRADEERR_UPLOADBLOCK_FAILED = 3,
	IMI_UPGRADEERR_CHECK_FAILED = 4,
	IMI_UPGRADEERR_DEVICE_DISCONNECT = 5,
}IMI_UPGRADE_ERRCODE;

#if defined(_WIN32)

typedef void (_stdcall * ImiDeviceUpgradeStepPromptUser) (IMI_UPGRADE_PROMPT promptID, float progress, IMI_UPGRADE_ERRCODE errCode, const char* errMsg, void* pUserData);

#else

typedef void (* ImiDeviceUpgradeStepPromptUser) (IMI_UPGRADE_PROMPT promptID, float progress, IMI_UPGRADE_ERRCODE errCode, const char* errMsg, void* pUserData);

#endif

typedef struct tagImiUpgradeCallbacks
{
	void* pUserData;
	ImiDeviceUpgradeStepPromptUser upgradeStepPromptProc;
} ImiUpgradeCallbacks;


typedef struct tagImiUpgradeRomPath
{
	char fw_RomPath[MAX_ADDRESSS_LEGTH];
	char uvc_color_RomPath[MAX_ADDRESSS_LEGTH];
	char bridge_fw_RomPath[MAX_ADDRESSS_LEGTH];

} ImiUpgradeRomPath;



/**
 * @brief  set the channel number for upgrade, use it to differentiate users, it's provided by hjimi,
           set it before open device. If not set it , use the default method to upgrade.

 * @param  const char* pChannelNo: the channel number
 * @return 0:success, < 0 :error
 **/
//IMINECT_EXP int32_t imiSetUpgradeChannelNo(const char* pChannelNo);

//IMINECT_EXP int32_t imiDeviceRequestUpgrade(ImiDeviceHandle pDevice);

//IMINECT_EXP int32_t imiDeviceStartUpgrade(ImiDeviceHandle pDevice, const ImiUpgradeCallbacks* pCallbacks);

IMINECT_EXP int32_t imiDeviceStartUpgradeOffLine(ImiDeviceHandle pDevice, const ImiUpgradeCallbacks* pCallbacks, const ImiUpgradeRomPath* pUpgradeRomPath);

#ifdef __cplusplus
}
#endif

#endif // _IMI_UPGRADE_H_

