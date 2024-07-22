// Copyright 2020-2021 Beken
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include <common/bk_include.h>
#include <driver/hal/hal_prro_types.h>

#define BK_ERR_PRRO_DRIVER_NOT_INIT             (BK_ERR_PRRO_BASE - 1) /**< PRRO driver not init */
#define BK_ERR_PRRO_DEV_ID                      (BK_ERR_PRRO_BASE - 2) /**< Invalid PRRO device ID */
#define BK_ERR_PRRO_MAP_TABLE                   (BK_ERR_PRRO_BASE - 3) /**< Invalid PRRO configuration map table */

#if CONFIG_TFM_BK7236_V5

typedef enum {
	PRRO_DEV_AON = 0,
	PRRO_DEV_AON_WDT,
	PRRO_DEV_APB_WDT,
	PRRO_DEV_AUD,
	PRRO_DEV_BTDM,
	PRRO_DEV_BTDM_M,
	PRRO_DEV_CAN,
	PRRO_DEV_CKMN,
	PRRO_DEV_DISP,
	PRRO_DEV_DISP_M,
	PRRO_DEV_DMA0,
	PRRO_DEV_DMA1,
	PRRO_DEV_DMAD,
	PRRO_DEV_DMAD_M,
	PRRO_DEV_EFS,
	PRRO_DEV_ENET,
	PRRO_DEV_ENET_M,
	PRRO_DEV_FLASH,
	PRRO_DEV_GPIOHIG,
	PRRO_DEV_H264,
	PRRO_DEV_HSU_M,
	PRRO_DEV_I2C0,
	PRRO_DEV_I2C1,
	PRRO_DEV_I2S0,
	PRRO_DEV_I2S1,
	PRRO_DEV_I2S2,
	PRRO_DEV_IRDA,
	PRRO_DEV_JPDEC_M,
	PRRO_DEV_JPENC_M,
	PRRO_DEV_JPGD,
	PRRO_DEV_JPGE,
	PRRO_DEV_LA,
	PRRO_DEV_LA_M,
	PRRO_DEV_LIN,
	PRRO_DEV_MAC,
	PRRO_DEV_MAC_M,
	PRRO_DEV_MBOX_AHB,
	PRRO_DEV_MCHECK,
	PRRO_DEV_MOD,
	PRRO_DEV_PPRO_MPC,
	PRRO_DEV_PSRAM,
	PRRO_DEV_PWM0,
	PRRO_DEV_PWM1,
	PRRO_DEV_QSPI0,
	PRRO_DEV_QSPI1,
	PRRO_DEV_REG,
	PRRO_DEV_ROTT,
	PRRO_DEV_ROTT_M,
	PRRO_DEV_RTC,
	PRRO_DEV_SADC,
	PRRO_DEV_SBC,
	PRRO_DEV_SCAL0,
	PRRO_DEV_SCAL0_M,
	PRRO_DEV_SCAL1,
	PRRO_DEV_SCAL1_M,
	PRRO_DEV_SCLD,
	PRRO_DEV_SCR,
	PRRO_DEV_SDIO,
	PRRO_DEV_SDMADC,
	PRRO_DEV_SPI0,
	PRRO_DEV_SPI1,
	PRRO_DEV_SYS,
	PRRO_DEV_TIMER0,
	PRRO_DEV_TIMER1,
	PRRO_DEV_TRNG,
	PRRO_DEV_UART0,
	PRRO_DEV_UART1,
	PRRO_DEV_UART2,
	PRRO_DEV_USB,
	PRRO_DEV_USB_M,
	PRRO_DEV_XVR,
	PRRO_DEV_YUV,
	PRRO_DEV_GPIO0,
	PRRO_DEV_GPIO1,
	PRRO_DEV_GPIO2,
	PRRO_DEV_GPIO3,
	PRRO_DEV_GPIO4,
	PRRO_DEV_GPIO5,
	PRRO_DEV_GPIO6,
	PRRO_DEV_GPIO7,
	PRRO_DEV_GPIO8,
	PRRO_DEV_GPIO9,
	PRRO_DEV_GPIO10,
	PRRO_DEV_GPIO11,
	PRRO_DEV_GPIO12,
	PRRO_DEV_GPIO13,
	PRRO_DEV_GPIO14,
	PRRO_DEV_GPIO15,
	PRRO_DEV_GPIO16,
	PRRO_DEV_GPIO17,
	PRRO_DEV_GPIO18,
	PRRO_DEV_GPIO19,
	PRRO_DEV_GPIO20,
	PRRO_DEV_GPIO21,
	PRRO_DEV_GPIO22,
	PRRO_DEV_GPIO23,
	PRRO_DEV_GPIO24,
	PRRO_DEV_GPIO25,
	PRRO_DEV_GPIO26,
	PRRO_DEV_GPIO27,
	PRRO_DEV_GPIO28,
	PRRO_DEV_GPIO29,
	PRRO_DEV_GPIO30,
	PRRO_DEV_GPIO31,
	PRRO_DEV_GPIO32,
	PRRO_DEV_GPIO33,
	PRRO_DEV_GPIO34,
	PRRO_DEV_GPIO35,
	PRRO_DEV_GPIO36,
	PRRO_DEV_GPIO37,
	PRRO_DEV_GPIO38,
	PRRO_DEV_GPIO39,
	PRRO_DEV_GPIO40,
	PRRO_DEV_GPIO41,
	PRRO_DEV_GPIO42,
	PRRO_DEV_GPIO43,
	PRRO_DEV_GPIO44,
	PRRO_DEV_GPIO45,
	PRRO_DEV_GPIO46,
	PRRO_DEV_GPIO47,
	PRRO_DEV_GPIO48,
	PRRO_DEV_GPIO49,
	PRRO_DEV_GPIO50,
	PRRO_DEV_GPIO51,
	PRRO_DEV_GPIO52,
	PRRO_DEV_GPIO53,
	PRRO_DEV_GPIO54,
	PRRO_DEV_GPIO55,

	PRRO_DEV_MAX,
} prro_dev_t;

#else

typedef enum {
	PRRO_DEV_AHB_AON = 0,
	PRRO_DEV_AHB_SYSTEM,
	PRRO_DEV_AHB_FLASH,
	PRRO_DEV_AHB_GDMA,
	PRRO_DEV_AHB_LA,
	PRRO_DEV_AHB_USB,
	PRRO_DEV_AHB_CAN,
	PRRO_DEV_AHB_QSPI0,
	PRRO_DEV_AHB_QSPI1,
	PRRO_DEV_AHB_PSRAM,
	PRRO_DEV_AHB_FFT,
	PRRO_DEV_AHB_SBC,
	PRRO_DEV_AHB_JPEG_ENC,
	PRRO_DEV_AHB_JPEG_DEC,
	PRRO_DEV_AHB_YUV,
	PRRO_DEV_AHB_LCD_DISP,
	PRRO_DEV_AHB_DMA2D,
	PRRO_DEV_AHB_ROTT,
	PRRO_DEV_AHB_WIFI_MAC,
	PRRO_DEV_AHB_WIFI_MODEM,
	PRRO_DEV_AHB_BTDM_AHB,
	PRRO_DEV_AHB_MBOX0,
	PRRO_DEV_AHB_MBOX1,
	PRRO_DEV_AHB_DMA1,
	PRRO_DEV_AHB_MAX,

	PRRO_DEV_APB_WDT,
	PRRO_DEV_APB_EFUSE,
	PRRO_DEV_APB_MBIC,
	PRRO_DEV_APB_SDMADC,
	PRRO_DEV_APB_TIMER0,
	PRRO_DEV_APB_TIMER1,
	PRRO_DEV_APB_PWM0,
	PRRO_DEV_APB_PWM1,
	PRRO_DEV_APB_UART0,
	PRRO_DEV_APB_UART1,
	PRRO_DEV_APB_UART2,
	PRRO_DEV_APB_SPI0,
	PRRO_DEV_APB_SPI1,
	PRRO_DEV_APB_I2C0,
	PRRO_DEV_APB_I2C1,
	PRRO_DEV_APB_SARADC,
	PRRO_DEV_APB_IRDA,
	PRRO_DEV_APB_TRNG,
	PRRO_DEV_APB_SDIO,
	PRRO_DEV_APB_SLCD,
	PRRO_DEV_APB_AUDIO,
	PRRO_DEV_APB_I2S0,
	PRRO_DEV_APB_I2S1,
	PRRO_DEV_APB_I2S2,
	PRRO_DEV_APB_VIDP,
	PRRO_DEV_APB_BTDM_APB,
	PRRO_DEV_APB_MAX,

	PRRO_DEV_AON_PMU,
	PRRO_DEV_AON_RTC,
	PRRO_DEV_AON_GPIO,
	PRRO_DEV_AON_WDT,
	PRRO_DEV_AON_MAX,

	PRRO_DEV_JPEC_ENC_HNONSEC,
	PRRO_DEV_JPEC_DEC_HNONSEC,
	PRRO_DEV_DMA2D_HNONSEC,
	PRRO_DEV_WIFI_MAC_HNONSEC,
	PRRO_DEV_HSU_HNONSEC,
	PRRO_DEV_BTDM_HNONSEC,
	PRRO_DEV_LA_HNONSEC,
	PRRO_DEV_LCD_DISP_HNONSEC,
	PRRO_DEV_ENC_HNONSEC,
	PRRO_DEV_MAX_HNONSEC,

	PRRO_DEV_GPIO_0,
	PRRO_DEV_GPIO_1,
	PRRO_DEV_GPIO_2,
	PRRO_DEV_GPIO_3,
	PRRO_DEV_GPIO_4,
	PRRO_DEV_GPIO_5,
	PRRO_DEV_GPIO_6,
	PRRO_DEV_GPIO_7,
	PRRO_DEV_GPIO_8,
	PRRO_DEV_GPIO_9,
	PRRO_DEV_GPIO_10,
	PRRO_DEV_GPIO_11,
	PRRO_DEV_GPIO_12,
	PRRO_DEV_GPIO_13,
	PRRO_DEV_GPIO_14,
	PRRO_DEV_GPIO_15,
	PRRO_DEV_GPIO_16,
	PRRO_DEV_GPIO_17,
	PRRO_DEV_GPIO_18,
	PRRO_DEV_GPIO_19,
	PRRO_DEV_GPIO_20,
	PRRO_DEV_GPIO_21,
	PRRO_DEV_GPIO_22,
	PRRO_DEV_GPIO_23,
	PRRO_DEV_GPIO_24,
	PRRO_DEV_GPIO_25,
	PRRO_DEV_GPIO_26,
	PRRO_DEV_GPIO_27,
	PRRO_DEV_GPIO_28,
	PRRO_DEV_GPIO_29,
	PRRO_DEV_GPIO_30,
	PRRO_DEV_GPIO_31,
	PRRO_DEV_GPIO_32,
	PRRO_DEV_GPIO_33,
	PRRO_DEV_GPIO_34,
	PRRO_DEV_GPIO_35,
	PRRO_DEV_GPIO_36,
	PRRO_DEV_GPIO_37,
	PRRO_DEV_GPIO_38,
	PRRO_DEV_GPIO_39,
	PRRO_DEV_GPIO_40,
	PRRO_DEV_GPIO_41,
	PRRO_DEV_GPIO_42,
	PRRO_DEV_GPIO_43,
	PRRO_DEV_GPIO_44,
	PRRO_DEV_GPIO_45,
	PRRO_DEV_GPIO_46,
	PRRO_DEV_GPIO_47,

	PRRO_DEV_MAX,
} prro_dev_t;

#endif

typedef enum {
	PRRO_PRIVILEGED = 0, /**< */
	PRRO_NON_PRIVILEGED,
} prro_privilege_type_t;

typedef enum {
	PRRO_SECURE = 0, /**<  */
	PRRO_NON_SECURE,
} prro_secure_type_t;

typedef enum {
	PRRO_CMP_0 = 0, /**<  */
	PRRO_CMP_1,
	PRRO_CMP_2,
	PRRO_CMP_COUNT,
} prro_cmp_id_t;
