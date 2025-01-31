message("source_list.cmake")

set(source_list ${source_list}
${PROJ_PATH}/src/main.c
${PROJ_PATH}/src/startup_stm32l552xx.s
${PROJ_PATH}/src/syscalls.c
${PROJ_PATH}/src/app/app.c
${PROJ_PATH}/src/bsp/bsp.c
${PROJ_PATH}/src/bsp/can/can.c
${PROJ_PATH}/src/bsp/clock/clock.c
${PROJ_PATH}/src/bsp/gpio/gpio.c
${PROJ_PATH}/src/bsp/uart/uart.c
${PROJ_PATH}/src/bsp/watchdog/watchdog.c
${PROJ_PATH}/src/utils/error/error.c
${PROJ_PATH}/src/utils/ring_buffer/ring_buffer.c
${PROJ_PATH}/src/tasks/task_handler.c
${PROJ_PATH}/src/tasks/media/media_task.c
${PROJ_PATH}/src/tasks/watchdog/wdog_task.c
)
