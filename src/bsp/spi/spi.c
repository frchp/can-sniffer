#include "spi.h"

#include "stm32l552xx.h"

/**
 * TODO : Interrupt driven SPI : SPI1_IRQHandler
 * TODO : initialize GPIO for SPI1
 */

void spi_Init(void)
{
  RCC->APB2ENR |= RCC_APB2ENR_SPI1EN; // Enable SPI1 clock

  SPI1->CR1 &= ~SPI_CR1_SPE; // Disable SPI1 before configuration
  SPI1->CR1 = SPI_CR1_MSTR | SPI_CR1_BR_0 | SPI_CR1_SSI | SPI_CR1_SSM; // Master mode, software CS, baud rate
  SPI1->CR2 = 0;
  SPI1->CR1 |= SPI_CR1_SPE; // Enable SPI1
}

void spi_Transmit(uint8_t data)
{
  while (!(SPI1->SR & SPI_SR_TXE)); // Wait until TX buffer is empty
  SPI1->DR = data;
}

uint8_t spi_Receive(void)
{
  while (!(SPI1->SR & SPI_SR_RXNE)); // Wait until RX buffer is full
  return SPI1->DR; // Return received data
}
