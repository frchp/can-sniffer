#ifndef _UART_H_
#define _UART_H_

#include <stdint.h>

void uart_init(void);
void uart_transmit(char *str, uint8_t size);

#endif // _UART_H_