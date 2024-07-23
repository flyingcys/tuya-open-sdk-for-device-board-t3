/**
* @file tkl_init_pm.h
* @brief Common process - tkl init cellular description
* @version 0.1
* @date 2021-08-06
*
* @copyright Copyright 2021-2030 Tuya Inc. All Rights Reserved.
*
*/
#ifndef __TKL_INIT_PM_H__
#define __TKL_INIT_PM_H__

#include "tkl_pm.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    OPERATE_RET             (*dev_unregistor)(const CHAR_T *devname);
    TUYA_PM_DEV_DESC_T*  (*get_dev_info)(const CHAR_T *devname);
    TUYA_PM_DEV_DESC_T*  (*get_dev_list_head)(void);
    OPERATE_RET     (*set_voltage)(const CHAR_T *devname, int mV);
    OPERATE_RET     (*get_voltage)(const CHAR_T *devname);
    OPERATE_RET     (*set_current)(const CHAR_T *devname,int mA);
    OPERATE_RET     (*get_current)(const CHAR_T *devname);
    OPERATE_RET     (*enable)(const CHAR_T *devname,int lp_en);
    OPERATE_RET     (*disable)(const CHAR_T *devname);
    OPERATE_RET     (*is_enable)(const CHAR_T *devname,BOOL_T *status);
    OPERATE_RET     (*power_off)(const CHAR_T *devname);
    OPERATE_RET     (*reset)(const CHAR_T *devname);
    OPERATE_RET     (*ioctl)(const CHAR_T *devname,int ctl_cmd,void *param);
}TKL_PM_INTF_T;

TKL_PM_INTF_T* tkl_pm_desc_get(VOID_T);

#ifdef __cplusplus
} // extern "C"
#endif

#endif