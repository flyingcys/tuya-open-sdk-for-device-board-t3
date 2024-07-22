TUYA_PLATFORM_DIR := $(dir $(lastword $(MAKEFILE_LIST)))/..


# tuya os adapter includes
TUYA_PLATFORM_CFLAGS := -I $(TUYA_PLATFORM_DIR)/../../adapter/system/include
TUYA_PLATFORM_CFLAGS += -I $(TUYA_PLATFORM_DIR)/../../adapter/system/include/driver
TUYA_PLATFORM_CFLAGS += -I $(TUYA_PLATFORM_DIR)/../../adapter/system/include/system
TUYA_PLATFORM_CFLAGS += -I $(TUYA_PLATFORM_DIR)/../../adapter/utilities/include

TUYA_PLATFORM_CFLAGS += -I $(TUYA_PLATFORM_DIR)/tuyaos/tuya_os_adapter/include
TUYA_PLATFORM_CFLAGS += -I $(TUYA_PLATFORM_DIR)/tuyaos/tuya_os_adapter/include/hostapd
TUYA_PLATFORM_CFLAGS += -I $(TUYA_PLATFORM_DIR)/tuyaos/tuya_os_adapter/include/lwip
TUYA_PLATFORM_CFLAGS += -I $(TUYA_PLATFORM_DIR)/tuyaos/tuya_os_adapter/include/tal_compatible
TUYA_PLATFORM_CFLAGS += -I $(TUYA_PLATFORM_DIR)/tuyaos/tuya_os_adapter/include/utilities/include

ifneq (${CONFIG_ENABLE_LWIP},y)
$(info ------ use bk lwip ------)
TUYA_PLATFORM_CFLAGS += -I $(TUYA_PLATFORM_DIR)/bk7236_os/armino/include
TUYA_PLATFORM_CFLAGS += -I $(TUYA_PLATFORM_DIR)/bk7236_os/tuya_build/bk7236/config
TUYA_PLATFORM_CFLAGS += -I $(TUYA_PLATFORM_DIR)/bk7236_os/armino/components/bk_rtos/include
TUYA_PLATFORM_CFLAGS += -I $(TUYA_PLATFORM_DIR)/bk7236_os/armino/middleware/driver/include/bk_private
TUYA_PLATFORM_CFLAGS += -I $(TUYA_PLATFORM_DIR)/bk7236_os/armino/components/lwip_intf_v2_1/lwip-2.1.2/port
TUYA_PLATFORM_CFLAGS += -I $(TUYA_PLATFORM_DIR)/bk7236_os/armino/components/lwip_intf_v2_1/lwip-2.1.2/src/include
TUYA_PLATFORM_CFLAGS += -I $(TUYA_PLATFORM_DIR)/bk7236_os/armino/components/lwip_intf_v2_1/lwip-2.1.2/src/include/compat
TUYA_PLATFORM_CFLAGS += -I $(TUYA_PLATFORM_DIR)/bk7236_os/armino/components/lwip_intf_v2_1/lwip-2.1.2/src/include/lwip
TUYA_PLATFORM_CFLAGS += -I $(TUYA_PLATFORM_DIR)/bk7236_os/armino/components/lwip_intf_v2_1/lwip-2.1.2/src/include/netif
else
$(info ------ use tuya lwip ------)
endif

TUYA_PLATFORM_CFLAGS += -g -Os -std=c99 -nostdlib -Wall -Wno-format -Wno-unknown-pragmas -Wno-address-of-packed-member -ffunction-sections -fsigned-char -fdata-sections -fno-strict-aliasing -ggdb -std=gnu99 -Wno-old-style-declaration -mcpu=cortex-m33+nodsp -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mcmse -end-group
