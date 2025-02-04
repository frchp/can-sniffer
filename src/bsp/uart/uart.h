#ifndef _UART_H_
#define _UART_H_

#include <stdint.h>

typedef void (*fpUartCallback)(void);

/**
  @brief Initialize LPUART1 peripheral and driver.
 */
void uart_init(void);

/**
  @brief Transmit given string.
 */
void uart_transmit(char *ac_str, uint8_t u8_size);

/**
  @brief Add listener for end of transmission.
 */
void uart_attach(fpUartCallback fp_listener);

#endif // _UART_H_