armino_build_get_property(armino_soc ARMINO_SOC)
armino_component_register()

file(GLOB common_libs ${CMAKE_CURRENT_SOURCE_DIR}/common/*.a)
foreach(lib ${common_libs})
	get_filename_component(lib_name ${lib} NAME)
	add_prebuilt_library(${lib_name} "${CMAKE_CURRENT_SOURCE_DIR}/common/${lib_name}")
	target_link_libraries(${COMPONENT_LIB} INTERFACE ${lib_name})
endforeach()

#file(GLOB libs ${CMAKE_CURRENT_SOURCE_DIR}/${armino_soc}/libs/*.a)
message(STATUS "path=$ENV{TUYA_PROJECT_DIR}/libs/libtuyaos.a")
file(GLOB libs "$ENV{TUYA_PROJECT_DIR}/libs/libtuyaos.a")

foreach(lib ${libs})
 	get_filename_component(lib_name ${lib} NAME)
    #add_prebuilt_library(${lib_name} "${CMAKE_CURRENT_SOURCE_DIR}/${armino_soc}/libs/${lib_name}")
 	add_prebuilt_library(${lib_name} "$ENV{TUYA_PROJECT_DIR}/libs/libtuyaos.a")
 	target_link_libraries(${COMPONENT_LIB} INTERFACE ${lib_name})
endforeach()

