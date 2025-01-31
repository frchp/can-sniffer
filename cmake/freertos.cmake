message("freertos.cmake")

set(FREERTOS_PORT GCC_ARM_CM33_NTZ_NONSECURE CACHE STRING "")

add_library(freertos_config INTERFACE)
target_include_directories(freertos_config SYSTEM INTERFACE 
${PROJ_PATH}/inc #FreeRTOSConfig.h
${PROJ_PATH}/src/tasks/idle # idle functions
# Arm drivers
${PROJ_PATH}/vendor/Device
${PROJ_PATH}/vendor/CMSIS
# error
${PROJ_PATH}/src/utils/error
)

target_compile_definitions(freertos_config
      INTERFACE
      projCOVERAGE_TEST=0)
