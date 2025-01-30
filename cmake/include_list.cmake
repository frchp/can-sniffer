message("include_list.cmake")

set(include_list ${include_list}
${PROJ_PATH}/src/app
${PROJ_PATH}/src/bsp
${PROJ_PATH}/src/bsp/can
${PROJ_PATH}/src/bsp/gpio
${PROJ_PATH}/src/bsp/uart
${PROJ_PATH}/src/bsp/watchdog
${PROJ_PATH}/src/utils/error
${PROJ_PATH}/src/utils/ring_buffer
${PROJ_PATH}/src
# ${PROJ_PATH}/inc
# tasks
${PROJ_PATH}/src/tasks
# vendor
${PROJ_PATH}/vendor/CMSIS
${PROJ_PATH}/vendor/Device
# config files
${CMAKE_BINARY_DIR}
)
