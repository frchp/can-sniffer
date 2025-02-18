cmake_minimum_required(VERSION 3.22)

# Setup cmake module path and compiler settings
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
message("Build type: "              ${CMAKE_BUILD_TYPE})
set(CMAKE_C_STANDARD                11)
set(CMAKE_C_STANDARD_REQUIRED       ON)
set(CMAKE_C_EXTENSIONS              ON)
set(CMAKE_CXX_STANDARD              17)
set(CMAKE_CXX_STANDARD_REQUIRED     ON)
set(CMAKE_CXX_EXTENSIONS            ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS		ON)
set(PROJ_PATH                       ${CMAKE_CURRENT_SOURCE_DIR})
set(DEP_PATH												${CMAKE_CURRENT_SOURCE_DIR}/build/_deps)
set(CMAKE_TOOLCHAIN_FILE			gcc-arm-none-eabi)

message("CAN SNIFFER")
list(APPEND CMAKE_MESSAGE_INDENT "|")
project(can-sniffer LANGUAGES C ASM)

include(${CMAKE_MODULE_PATH}/config.cmake)
include(${CMAKE_MODULE_PATH}/freertos.cmake)
include(${CMAKE_MODULE_PATH}/dependencies.cmake)

set(linker_script_SRC               ${PROJ_PATH}/linker_script.ld)
set(EXECUTABLE                      ${CMAKE_PROJECT_NAME})

include(${CMAKE_MODULE_PATH}/source_list.cmake)
include(${CMAKE_MODULE_PATH}/include_list.cmake)
include(${CMAKE_MODULE_PATH}/stm32l5xx.cmake)

# Executable files
add_executable(${EXECUTABLE} ${source_list})

# Include paths
target_include_directories(${EXECUTABLE} PRIVATE ${include_list})

# Project symbols
target_compile_definitions(${EXECUTABLE} PRIVATE ${compiler_define})

# Compiler options
set(COMPILE_OPTIONS_PROJECT ${COMPILE_OPTIONS_PROJECT}
	${CPU_PARAMETERS}
	-Wall
	-Wpedantic
	-Wno-unused-parameter
)

target_compile_options(${EXECUTABLE} PRIVATE
	${COMPILE_OPTIONS_PROJECT}
)

# Linker options
set(LINK_OPTIONS_PROJECT ${LINK_OPTIONS_PROJECT}
	-T${linker_script_SRC}
	${CPU_PARAMETERS}
	-Wl,-Map=${CMAKE_PROJECT_NAME}.map
	--specs=nosys.specs
	-Wl,--start-group
	-lc
	-lm
	-lstdc++
	-lsupc++
	-Wl,--end-group
	-Wl,--print-memory-usage
)

target_link_options(${EXECUTABLE} PRIVATE
	${LINK_OPTIONS_PROJECT}
)

# Include libraries
# Transmit options to FreeRTOS for cross compilation
target_compile_options(freertos_config INTERFACE
	${COMPILE_OPTIONS_PROJECT}
)
target_link_options(freertos_config INTERFACE
	${LINK_OPTIONS_PROJECT}
)
target_link_libraries(${EXECUTABLE} PRIVATE freertos_kernel)

# Execute post-build to print size
add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
	COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${EXECUTABLE}>
)

# Convert output to hex and binary
add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
	COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${EXECUTABLE}> ${EXECUTABLE}.hex
)

# Convert to bin file -> add conditional check?
add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
	COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${EXECUTABLE}> ${EXECUTABLE}.bin
)

list(POP_BACK CMAKE_MESSAGE_INDENT)