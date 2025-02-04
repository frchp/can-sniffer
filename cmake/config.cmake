message("config.cmake")

set(UART_MAX_SIZE 200)
configure_file(${PROJ_PATH}/src/bsp/uart/uart_config.h.in ${CMAKE_BINARY_DIR}/uart_config.h)
