#include "uart.h"
#include "uart_config.h"

#include "stm32l552xx.h"

/* TODO : use static buffer*/
#include <stddef.h>
volatile char *uart_tx_buffer = NULL;

/* Private functions */
static void uart_send_next_char(void);

void uart_init(void)
{
  RCC->APB1ENR2 |= RCC_APB1ENR2_LPUART1EN;
  // Configure baud rate (Assuming 80MHz clock, 115200 baud)
  LPUART1->BRR = 6944;
  LPUART1->CR1 |= USART_CR1_TE | USART_CR1_UE | USART_CR1_TXEIE;
  NVIC_EnableIRQ(LPUART1_IRQn);
}

void uart_transmit(char *str, uint8_t size)
{
  /* TODO : memcpy into static buffer, check max size + use previous implementation */
  uart_tx_buffer = str;
  uart_send_next_char();
}

void LPUART1_IRQHandler(void)
{
  if (LPUART1->ISR & USART_ISR_TXE)
  {
    /* TODO : clear flag */
    uart_send_next_char();
  }
}

static void uart_send_next_char(void)
{
  if (uart_tx_buffer && *uart_tx_buffer) {
    LPUART1->TDR = *uart_tx_buffer++;
  }
  else
  {
    uart_tx_buffer = NULL;
    LPUART1->CR1 &= ~USART_CR1_TXEIE; // Disable TXE interrupt when done
  }
}
