/**
 * @file tkl_system.c
 * @brief the default weak implements of tuya os system api, this implement only used when OS=linux
 * @version 0.1
 * @date 2019-08-15
 *
 * @copyright Copyright 2020-2021 Tuya Inc. All Rights Reserved.
 *
 */

#include "tkl_system.h"
#include "FreeRTOS.h"
#include "task.h"
#include <os/os.h>
#include <components/system.h>
#include "reset_reason.h"
#include <driver/trng.h>
#include "tkl_memory.h"
/**
* @brief Get system ticket count
*
* @param VOID
*
* @note This API is used to get system ticket count.
*
* @return system ticket count
*/
SYS_TICK_T tkl_system_get_tick_count(VOID_T)
{
    return (SYS_TICK_T)xTaskGetTickCount();
}

/**
* @brief Get system millisecond
*
* @param none
*
* @return system millisecond
*/
SYS_TIME_T tkl_system_get_millisecond(VOID_T)
{
    return (SYS_TIME_T)(tkl_system_get_tick_count() * portTICK_RATE_MS);
}

/**
* @brief System sleep
*
* @param[in] msTime: time in MS
*
* @note This API is used for system sleep.
*
* @return VOID
*/
VOID_T tkl_system_sleep(CONST UINT_T num_ms)
{
    UINT_T ticks = num_ms / portTICK_RATE_MS;

    if (ticks == 0) {
        ticks = 1;
    }

    vTaskDelay(ticks);
}


/**
* @brief System reset
*
* @param VOID
*
* @note This API is used for system reset.
*
* @return VOID
*/
VOID_T tkl_system_reset(VOID_T)
{
    bk_reboot();
	return;
}

/**
* @brief Get free heap size
*
* @param VOID
*
* @note This API is used for getting free heap size.
*
* @return size of free heap
*/
int32_t tkl_system_get_free_heap_size(VOID_T)
{
    return (int32_t)xPortGetFreeHeapSize();
}

/**
* @brief Get system reset reason
*
* @param VOID
*
* @note This API is used for getting system reset reason.
*
* @return reset reason of system
*/
TUYA_RESET_REASON_E tkl_system_get_reset_reason(CHAR_T** describe)
{
    unsigned char value = bk_misc_get_reset_reason() & 0xFF;
    TUYA_RESET_REASON_E ty_value;

    switch (value) {
        case RESET_SOURCE_POWERON:
            ty_value = TUYA_RESET_REASON_POWERON;
            break;

        case RESET_SOURCE_REBOOT:
            ty_value = TUYA_RESET_REASON_SOFTWARE;
            break;

        case RESET_SOURCE_WATCHDOG:
        case RESET_SOURCE_NMI_WDT:
            ty_value = TUYA_RESET_REASON_HW_WDOG;
            break;

        case RESET_SOURCE_DEEPPS_GPIO:
        case RESET_SOURCE_DEEPPS_RTC:
        case RESET_SOURCE_DEEPPS_USB:
        case RESET_SOURCE_DEEPPS_TOUCH:
            ty_value = TUYA_RESET_REASON_DEEPSLEEP;
            break;

        // case RESET_SOURCE_CRASH_XAT0:
        case RESET_SOURCE_CRASH_UNDEFINED:
        case RESET_SOURCE_CRASH_PREFETCH_ABORT:
        case RESET_SOURCE_CRASH_DATA_ABORT:
        case RESET_SOURCE_CRASH_UNUSED:
        // case RESET_SOURCE_CRASH_PER_XAT0:
            ty_value = TUYA_RESET_REASON_FAULT;
            break;

        default:
            ty_value = TUYA_RESET_REASON_UNKNOWN;
            break;

    }

    bk_printf("bk_value:%d, ty_value:%d\r\n", value, ty_value);
    return ty_value;

}

/**
* @brief Get a random number in the specified range
*
* @param[in] range: range
*
* @note This API is used for getting a random number in the specified range
*
* @return a random number in the specified range
*/
int32_t tkl_system_get_random(CONST UINT_T range)
{
    unsigned int trange = range;

    if (range == 0) {
        trange = 0xFF;
    }

    static char exec_flag = FALSE;

    if (!exec_flag) {
        exec_flag = TRUE;
    }

    return (bk_rand() % trange);
}

#define EFUSE_DEVICE_ID_BYTE_NUM 5
#define OTP_DEVICE_ID 30

OPERATE_RET tkl_system_get_cpu_info(TUYA_CPU_INFO_T **cpu_ary, int32_t *cpu_cnt)
{
    TUYA_CPU_INFO_T *cpu = tkl_system_malloc(sizeof(TUYA_CPU_INFO_T));
    if (NULL == cpu) {
        return OPRT_MALLOC_FAILED;
    }
    memset(cpu, 0, sizeof(TUYA_CPU_INFO_T));
    bk_otp_apb_read(OTP_DEVICE_ID, cpu->chipid, EFUSE_DEVICE_ID_BYTE_NUM);
    cpu->chipidlen = EFUSE_DEVICE_ID_BYTE_NUM;
    if (cpu_cnt) {
        *cpu_cnt = 1;
    }

    *cpu_ary = cpu;

    return OPRT_OK;
}
