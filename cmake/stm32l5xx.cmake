message("stm32l5xx.cmake")

set(CPU_PARAMETERS ${CPU_PARAMETERS}
    -mthumb
    -mcpu=cortex-m33
    -mfpu=fpv5-sp-d16
    -mfloat-abi=hard
)

set(compiler_define ${compiler_define}
    "STM32L552xx"
)