/*
 * Copyright (c) 2018-2019, Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "platform/include/tfm_platform_system.h"
#include "cmsis.h"
#include "soc/soc.h"
#include "aon_pmu_hal.h"
#include "prro_hal.h"

static void tfm_platform_set_reset_reason(uint32_t type)
{
	/* use PMU_REG0 bit[24:27] for reset reason */
	uint32_t misc_value = aon_pmu_ll_get_r0();
	misc_value |= ((type & 0xf) << 24);
	aon_pmu_ll_set_r0(misc_value);

	/* pass PMU_REGO value to PMU_REG7B*/
	aon_pmu_ll_set_r25(0x424B55AA);
	aon_pmu_ll_set_r25(0xBDB4AA55);
}

static void tfm_platform_wdt_reset(void)
{
    //TODO fix me, please consider bk_reboot in Armino
    //
    printf("wdt reboot\r\n");
#if CONFIG_TFM_BK7236_V5
    prro_hal_set_secure(PRRO_DEV_REG, PRRO_SECURE);
#else
    prro_hal_set_secure(PRRO_DEV_AON_PMU, PRRO_SECURE);
#endif
    prro_hal_set_secure(PRRO_DEV_AON_WDT, PRRO_SECURE);
    prro_hal_set_secure(PRRO_DEV_APB_WDT, PRRO_SECURE);
    tfm_platform_set_reset_reason(RESET_SOURCE_REBOOT);
    __disable_irq();
    REG_WRITE(SOC_AON_WDT_REG_BASE, 0x5A000A);
    REG_WRITE(SOC_AON_WDT_REG_BASE, 0xA5000A);
    while(1);
}

void tfm_platform_hal_system_reset(void)
{
    /* Reset the system */

    //NVIC_SystemReset();
    tfm_platform_wdt_reset();
}


enum tfm_platform_err_t tfm_platform_hal_ioctl(tfm_platform_ioctl_req_t request,
                                               psa_invec  *in_vec,
                                               psa_outvec *out_vec)
{
    (void)request;
    (void)in_vec;
    (void)out_vec;

    /* Not needed for this platform */
    return TFM_PLATFORM_ERR_NOT_SUPPORTED;
}

