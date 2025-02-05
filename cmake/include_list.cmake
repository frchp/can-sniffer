message("include_list.cmake")

set(include_list ${include_list}
# application
${PROJ_PATH}/src/app
${PROJ_PATH}/src/app/hmi
${PROJ_PATH}/src/app/mcp2551
${PROJ_PATH}/src/app/transmitter
# bsp
${PROJ_PATH}/src/bsp
${PROJ_PATH}/src/bsp/can
${PROJ_PATH}/src/bsp/clock
${PROJ_PATH}/src/bsp/gpio
${PROJ_PATH}/src/bsp/i2c
${PROJ_PATH}/src/bsp/uart
${PROJ_PATH}/src/bsp/watchdog
# utils
${PROJ_PATH}/src/utils/error
# root
${PROJ_PATH}/src
${PROJ_PATH}/inc
# tasks
${PROJ_PATH}/src/tasks
${PROJ_PATH}/src/tasks/hmi
${PROJ_PATH}/src/tasks/idle
${PROJ_PATH}/src/tasks/media
${PROJ_PATH}/src/tasks/watchdog
# vendor
${PROJ_PATH}/vendor/CMSIS
${PROJ_PATH}/vendor/Device
# config files
${CMAKE_BINARY_DIR}
)
