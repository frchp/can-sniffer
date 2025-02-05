#ifndef _SPI_H_
#define _SPI_H_

#include <stdint.h>

void spi_Init(void);

void spi_Transmit(uint8_t data);

uint8_t spi_Receive(void);

#endif // _SPI_H_