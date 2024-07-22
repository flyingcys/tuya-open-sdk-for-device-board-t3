set(incs)
set(srcs)

#自动查找头文件路径函数
macro(FIND_INCLUDE_DIR result curdir)                                               ## 定义函数,2个参数:存放结果result；指定路径curdir；
    file(GLOB_RECURSE children "${curdir}/*.h")                                     ## 遍历获取{curdir}中*.hpp和*.h文件列表
    set(dirlist "")                                                                 ## 定义dirlist中间变量，并初始化
    foreach(child ${children})                                                      ## for循环
        string(REGEX REPLACE "(.*)/.*" "\\1" DIR_NAME ${child})                     ## 字符串替换,用/前的字符替换/*h
        if((IS_DIRECTORY ${DIR_NAME}) AND (NOT (${DIR_NAME} IN_LIST dirlist)))      ## 判断是否为路径
            list(APPEND dirlist ${DIR_NAME})                                        ## 将合法的路径加入dirlist变量中
        endif()                                                                     ## 结束判断
    endforeach()                                                                    ## 结束for循环
    set(${result} ${dirlist})                                                       ## dirlist结果放入result变量中
    #message(STATUS "result=${dirlist}")                                            ## 打印*.hpp和*.h的文件列表
endmacro()

#add tuya include dir
set(INCLUDE_DIR_LIST_TUYA $ENV{TUYA_HEADER_DIR})
# 将路径列表转换为 CMake 中的列表变量
string(REPLACE " " ";" INCLUDE_DIR_LIST_TUYA "${INCLUDE_DIR_LIST_TUYA}")
set(incs ${INCLUDE_DIR_LIST_TUYA})


list(APPEND srcs
	"src/driver/tkl_adc.c"
	"src/driver/tkl_flash.c"
	"src/driver/tkl_gpio.c"
	"src/driver/tkl_hci.c"
	"src/driver/tkl_lwip.c"
	"src/driver/tkl_pwm.c"
	"src/driver/tkl_rtc.c"
	"src/driver/tkl_spi.c"
	"src/driver/tkl_i2c.c"
	"src/driver/tkl_timer.c"
	"src/driver/tkl_uart.c"
	"src/driver/tkl_watchdog.c"
	"src/driver/tkl_wifi.c"
	"src/system/tkl_memory.c"
	"src/system/tkl_mutex.c"
	"src/system/tkl_network.c"
	"src/system/tkl_ota.c"
	"src/system/tkl_output.c"
	"src/system/tkl_queue.c"
	"src/system/tkl_semaphore.c"
	"src/system/tkl_sleep.c"
	"src/system/tkl_system.c"
	"src/system/tkl_thread.c"
	"src/driver/tkl_pinmux.c"
	"src/driver/tkl_wakeup.c"
)

file(GLOB_RECURSE utilities_srcs "$ENV{ARMINO_PATH}/../../tuyaos/tuyaos_adapter/include/utilities/src/*.c")
list(APPEND srcs ${utilities_srcs})
#add incs srcs

set(lwip_select $ENV{TUYA_LWIP_STACK_USED})
if (lwip_select STREQUAL "lwip_bk")
    armino_component_register(SRCS "${srcs}" INCLUDE_DIRS "${incs}" REQUIRES bk_common bk_log lwip_intf_v2_1)
else ()
    armino_component_register(SRCS "${srcs}" INCLUDE_DIRS "${incs}" REQUIRES bk_common bk_log)
endif()

#add tuya lib
set(tuya_libs "$ENV{TUYA_LIBS}")
string(REPLACE " " ";" tuya_libs "${tuya_libs}")
foreach(lib ${tuya_libs})	
	set(lib_name "lib${lib}.a")
    add_prebuilt_library(${lib_name} "$ENV{TUYA_LIBS_DIR}/${lib_name}")
    target_link_libraries(${COMPONENT_LIB} INTERFACE ${lib_name})
endforeach()