// Copyright 2022-2023 Beken
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

#include "sdkconfig.h"

#define SOC_S_NS_ADDR_DIFF       (0x10000000)

#if CONFIG_SPE
#define SOC_ADDR_OFFSET          (0)
#define SOC_GET_S_ADDR(addr)     (addr)
#define SOC_GET_NS_ADDR(addr)    ((addr) + SOC_S_NS_ADDR_DIFF)
#else
#define SOC_ADDR_OFFSET          SOC_S_NS_ADDR_DIFF
#define SOC_GET_S_ADDR(addr)     ((addr) - SOC_S_NS_ADDR_DIFF)
#define SOC_GET_NS_ADDR(addr)    (addr)
#endif

#define SOC_ITCM_DATA_BASE       (0x00000000 + SOC_ADDR_OFFSET)
#define SOC_DTCM_DATA_BASE       (0x20000000 + SOC_ADDR_OFFSET)

#define SOC_FLASH_DATA_BASE      (0x02000000 + SOC_ADDR_OFFSET)
#define SOC_ROM_DATA_BASE        (0x06000000 + SOC_ADDR_OFFSET)
#define SOC_SRAM0_DATA_BASE      (0x28000000 + SOC_ADDR_OFFSET) //64K
#define SOC_SRAM1_DATA_BASE      (0x28010000 + SOC_ADDR_OFFSET) //64K
#define SOC_SRAM2_DATA_BASE      (0x28020000 + SOC_ADDR_OFFSET) //128K
#define SOC_SRAM3_DATA_BASE      (0x28040000 + SOC_ADDR_OFFSET) //128K
#define SOC_SRAM4_DATA_BASE      (0x28060000 + SOC_ADDR_OFFSET) //128K
#define SOC_SRAM5_DATA_BASE      (0x28080000 + SOC_ADDR_OFFSET) //128K

#define SOC_PSRAM_DATA_BASE      (0x60000000 + SOC_ADDR_OFFSET)
#define SOC_QSPI0_DATA_BASE      (0x64000000 + SOC_ADDR_OFFSET)
#define SOC_QSPI1_DATA_BASE      (0x68000000 + SOC_ADDR_OFFSET)

#define SOC_PSRAM_DATA_SIZE      (0x4000000)
#define SOC_QSPI0_DATA_SIZE      (0x4000000)
#define SOC_QSPI1_DATA_SIZE      (0x4000000)

#define SOC_SYS_REG_BASE         (0x44010000 + SOC_ADDR_OFFSET)
#define SOC_SYSTEM_REG_BASE      (0x44010000 + SOC_ADDR_OFFSET)

#define SOC_AON_PMU_REG_BASE     (0x44000000 + SOC_ADDR_OFFSET)

#define SOC_MPC_PSRAM_REG_BASE   (0x41100000 + SOC_ADDR_OFFSET)
#define SOC_MPC_QSPI0_REG_BASE   (0x41110000 + SOC_ADDR_OFFSET)
#define SOC_MPC_QSPI1_REG_BASE   (0x41120000 + SOC_ADDR_OFFSET)
#define SOC_MPC_OTP_REG_BASE     (0x41130000 + SOC_ADDR_OFFSET)
#define SOC_MPC_FLASH_REG_BASE   (0x41200000 + SOC_ADDR_OFFSET)
#define SOC_MPC_SMEM0_REG_BASE   (0x41210000 + SOC_ADDR_OFFSET)
#define SOC_MPC_SMEM1_REG_BASE   (0x41220000 + SOC_ADDR_OFFSET)
#define SOC_MPC_SMEM2_REG_BASE   (0x41230000 + SOC_ADDR_OFFSET)
#define SOC_MPC_SMEM3_REG_BASE   (0x41240000 + SOC_ADDR_OFFSET)
#define SOC_MPC_SMEM4_REG_BASE   (0x41250000 + SOC_ADDR_OFFSET)
#define SOC_MPC_SMEM5_REG_BASE   (0x41260000 + SOC_ADDR_OFFSET)

#define SOC_AON_WDT_REG_BASE     (0x44000600 + SOC_ADDR_OFFSET)
#define SOC_AON_GPIO_REG_BASE    (0x44000400 + SOC_ADDR_OFFSET)
#define SOC_AON_RTC_REG_BASE     (0x44000200 + SOC_ADDR_OFFSET)
#define SOC_FLASH_REG_BASE       (0x44030000 + SOC_ADDR_OFFSET)
#define SOC_MBOX0_REG_BASE       (0x41000000 + SOC_ADDR_OFFSET)
#define SOC_MBOX1_REG_BASE       (0x41020000 + SOC_ADDR_OFFSET)
#define SOC_GENER_DMA_REG_BASE   (0x45020000 + SOC_ADDR_OFFSET)
#define SOC_GENER_DMA1_REG_BASE  (0x45030000 + SOC_ADDR_OFFSET)
#define SOC_PSRAM_REG_BASE       (0x46080000 + SOC_ADDR_OFFSET)
#define SOC_SBC_REG_BASE         (0x47010000 + SOC_ADDR_OFFSET)
#define SOC_UART0_REG_BASE       (0x44820000 + SOC_ADDR_OFFSET)
#define SOC_UART1_REG_BASE       (0x45830000 + SOC_ADDR_OFFSET)
#define SOC_UART2_REG_BASE       (0x45840000 + SOC_ADDR_OFFSET)

#define SOC_CAN_REG_BASE         (0x46020000 + SOC_ADDR_OFFSET)
#define SOC_WDT_REG_BASE         (0x44800000 + SOC_ADDR_OFFSET)
#define SOC_TIMER0_REG_BASE      (0x44810000 + SOC_ADDR_OFFSET)
#define SOC_SPI_REG_BASE         (0x44870000 + SOC_ADDR_OFFSET)
#define SOC_EFUSE_REG_BASE       (0x44880000 + SOC_ADDR_OFFSET)
#define SOC_MEM_CHECK_REG_BASE   (0x44890000 + SOC_ADDR_OFFSET)
#define SOC_CKMN_REG_BASE        (0x448A0000 + SOC_ADDR_OFFSET)

#define SOC_SPI1_REG_BASE        (0x45880000 + SOC_ADDR_OFFSET)
#define SOC_I2C0_REG_BASE        (0x45850000 + SOC_ADDR_OFFSET)
#define SOC_I2C1_REG_BASE        (0x45860000 + SOC_ADDR_OFFSET)
#define SOC_TIMER1_REG_BASE      (0x45800000 + SOC_ADDR_OFFSET)
#define SOC_PWM_REG_BASE         (0x458a0000 + SOC_ADDR_OFFSET)
#define SOC_SDMADC_REG_BASE      (0x45810000 + SOC_ADDR_OFFSET)
#define SOC_SADC_REG_BASE        (0x45890000 + SOC_ADDR_OFFSET)
#define SOC_IRDA_REG_BASE        (0x458b0000 + SOC_ADDR_OFFSET)

#define SOC_AUD_REG_BASE         (0x47800000 + SOC_ADDR_OFFSET)
#define SOC_I2S_REG_BASE         (0x47810000 + SOC_ADDR_OFFSET)
#define SOC_I2S1_REG_BASE        (0x47820000 + SOC_ADDR_OFFSET)
#define SOC_I2S2_REG_BASE        (0x47830000 + SOC_ADDR_OFFSET)
#define SOC_TRNG_REG_BASE        (0x458C0000 + SOC_ADDR_OFFSET)
#define SOC_XVR_REG_BASE         (0x4A800000 + SOC_ADDR_OFFSET)
#define SOC_LA_REG_BASE          (0x45070000 + SOC_ADDR_OFFSET)
#define SOC_JPEG_REG_BASE        (0x48000000 + SOC_ADDR_OFFSET)
#define SOC_JPEG_DEC_REG_BASE    (0x48040000 + SOC_ADDR_OFFSET)
#define SOC_YUV_BUF_REG_BASE     (0x48020000 + SOC_ADDR_OFFSET)
#define SOC_OTP_REG_BASE         (0x0b100000 + SOC_ADDR_OFFSET)
#define SOC_PRRO_REG_BASE        (0x41040000 + SOC_ADDR_OFFSET)
#define SOC_PPRO_REG_BASE        (0x41040000 + SOC_ADDR_OFFSET)

#define SOC_USB_REG_BASE         (0x46000000 + SOC_ADDR_OFFSET)
#define SOC_QSPI0_REG_BASE       (0x46040000 + SOC_ADDR_OFFSET)
#define SOC_QSPI2_REG_BASE       (0x46060000 + SOC_ADDR_OFFSET)
#define SOC_ENET_REG_BASE        (0x460A0000 + SOC_ADDR_OFFSET)
#define SOC_SCR_REG_BASE         (0x46100000 + SOC_ADDR_OFFSET)
#define SOC_LIN_REG_BASE         (0x46110000 + SOC_ADDR_OFFSET)

#define SOC_H264_REG_BASE        (0x480A0000 + SOC_ADDR_OFFSET)
#define SOC_LCD_DISP_REG_BASE    (0x48060000 + SOC_ADDR_OFFSET)
#define SOC_SDIO_REG_BASE        (0x458d0000 + SOC_ADDR_OFFSET)
#define SOC_SLCD_REG_BASE        (0x458e0000 + SOC_ADDR_OFFSET)
#define SOC_RC_REG_BASE          (0x4980C000 + SOC_ADDR_OFFSET)
#define SOC_TRX_REG_BASE         (0x4980C200 + SOC_ADDR_OFFSET)
#define SOC_POWTBL_REG_BASE      (0x4980C400 + SOC_ADDR_OFFSET)
#define SOC_DPDTBL_REG_BASE      (0x49840000 + SOC_ADDR_OFFSET)
#define SOC_AGCMEM_REG_BASE      (0x4980A000 + SOC_ADDR_OFFSET)
#define SOC_PEAKCWMEM_REG_BASE   (0x4980D000 + SOC_ADDR_OFFSET)
#define SOC_DMA2D_REG_BASE       (0x48080000 + SOC_ADDR_OFFSET)
#define SOC_ROTT_REG_BASE        (0x480c0000 + SOC_ADDR_OFFSET)
#define SOC_SCAL0_REG_BASE       (0x480D0000 + SOC_ADDR_OFFSET)
#define SOC_SCAL1_REG_BASE       (0x480E0000 + SOC_ADDR_OFFSET)

#define SOC_BKRW_REG_BASE        (0x4a010000 + SOC_ADDR_OFFSET)
#define SOC_OTP_AHB_BASE         (0x4b010000 + SOC_ADDR_OFFSET)
#define SOC_OTP_APB_BASE         (0x4b100000 + SOC_ADDR_OFFSET)
#define SOC_SHANHAI_BASE         (0x4b110000 + SOC_ADDR_OFFSET)
//eof

