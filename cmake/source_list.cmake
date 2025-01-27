message("source_list.cmake")

set(source_list ${source_list}
${PROJ_PATH}/src/main.c
${PROJ_PATH}/src/startup_stm32l552xx.s
${PROJ_PATH}/src/syscalls.c
${PROJ_PATH}/src/app/app.c
${PROJ_PATH}/src/app/direction_controller/direction_controller.c
${PROJ_PATH}/src/app/intensity_sensor/intensity_sensor.c
${PROJ_PATH}/src/app/motor_controller/motor_controller.c
${PROJ_PATH}/src/app/order_handler/order_handler.c
${PROJ_PATH}/src/app/speed_sensor/speed_sensor.c
${PROJ_PATH}/src/bsp/bsp.c
${PROJ_PATH}/src/bsp/adc/adc.c
${PROJ_PATH}/src/bsp/gpio/gpio.c
${PROJ_PATH}/src/bsp/interrupts/interrupts.c
${PROJ_PATH}/src/bsp/system/system.c
${PROJ_PATH}/src/bsp/timer_counter/timer_counter.c
${PROJ_PATH}/src/bsp/timer_pwm/timer_pwm.c
${PROJ_PATH}/src/bsp/uart/uart.c
${PROJ_PATH}/src/bsp/watchdog/watchdog.c
${PROJ_PATH}/src/utils/ring_buffer/ring_buffer.c
# tasks
${PROJ_PATH}/src/tasks/task_handler.c
${PROJ_PATH}/src/tasks/idle/idle_task.c
${PROJ_PATH}/src/tasks/media/media_task.c
${PROJ_PATH}/src/tasks/motor/motor_task.c
${PROJ_PATH}/src/tasks/watchdog/wdog_task.c
# vendor
${PROJ_PATH}/vendor/STM32L5xx_HAL_Driver/Src/stm32l5xx_ll_adc.c
${PROJ_PATH}/vendor/STM32L5xx_HAL_Driver/Src/stm32l5xx_ll_comp.c
${PROJ_PATH}/vendor/STM32L5xx_HAL_Driver/Src/stm32l5xx_ll_crc.c
${PROJ_PATH}/vendor/STM32L5xx_HAL_Driver/Src/stm32l5xx_ll_crs.c
${PROJ_PATH}/vendor/STM32L5xx_HAL_Driver/Src/stm32l5xx_ll_dac.c
${PROJ_PATH}/vendor/STM32L5xx_HAL_Driver/Src/stm32l5xx_ll_dma.c
${PROJ_PATH}/vendor/STM32L5xx_HAL_Driver/Src/stm32l5xx_ll_exti.c
${PROJ_PATH}/vendor/STM32L5xx_HAL_Driver/Src/stm32l5xx_ll_fmc.c
${PROJ_PATH}/vendor/STM32L5xx_HAL_Driver/Src/stm32l5xx_ll_gpio.c
${PROJ_PATH}/vendor/STM32L5xx_HAL_Driver/Src/stm32l5xx_ll_i2c.c
${PROJ_PATH}/vendor/STM32L5xx_HAL_Driver/Src/stm32l5xx_ll_icache.c
${PROJ_PATH}/vendor/STM32L5xx_HAL_Driver/Src/stm32l5xx_ll_lptim.c
${PROJ_PATH}/vendor/STM32L5xx_HAL_Driver/Src/stm32l5xx_ll_lpuart.c
${PROJ_PATH}/vendor/STM32L5xx_HAL_Driver/Src/stm32l5xx_ll_opamp.c
${PROJ_PATH}/vendor/STM32L5xx_HAL_Driver/Src/stm32l5xx_ll_pka.c
${PROJ_PATH}/vendor/STM32L5xx_HAL_Driver/Src/stm32l5xx_ll_pwr.c
${PROJ_PATH}/vendor/STM32L5xx_HAL_Driver/Src/stm32l5xx_ll_rcc.c
${PROJ_PATH}/vendor/STM32L5xx_HAL_Driver/Src/stm32l5xx_ll_rng.c
${PROJ_PATH}/vendor/STM32L5xx_HAL_Driver/Src/stm32l5xx_ll_rtc.c
${PROJ_PATH}/vendor/STM32L5xx_HAL_Driver/Src/stm32l5xx_ll_sdmmc.c
${PROJ_PATH}/vendor/STM32L5xx_HAL_Driver/Src/stm32l5xx_ll_spi.c
${PROJ_PATH}/vendor/STM32L5xx_HAL_Driver/Src/stm32l5xx_ll_tim.c
${PROJ_PATH}/vendor/STM32L5xx_HAL_Driver/Src/stm32l5xx_ll_ucpd.c
${PROJ_PATH}/vendor/STM32L5xx_HAL_Driver/Src/stm32l5xx_ll_usart.c
${PROJ_PATH}/vendor/STM32L5xx_HAL_Driver/Src/stm32l5xx_ll_usb.c
${PROJ_PATH}/vendor/STM32L5xx_HAL_Driver/Src/stm32l5xx_ll_utils.c
)
