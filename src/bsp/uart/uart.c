#include "uart.h"
#include "uart_config.h"

#include "stm32l552xx.h"
#include <stddef.h>
#include "FreeRTOSConfig.h"
#include <string.h> // memcpy

static char uart_tx_buffer[UART_MAX_SIZE];
static volatile uint8_t uart_tx_size = 0u;
static volatile uint8_t uart_tx_idx = 0u;

/* Private functions */
static void uart_send_next_char(void);

void uart_init(void)
{
  RCC->APB1ENR2 |= RCC_APB1ENR2_LPUART1EN;
  // Configure baud rate (Assuming 80MHz clock, 115200 baud)
  LPUART1->BRR = 6944;
  LPUART1->CR1 |= USART_CR1_TE | USART_CR1_UE | USART_CR1_TCIE;
  NVIC_EnableIRQ(LPUART1_IRQn);
  NVIC_SetPriority(LPUART1_IRQn, configMAX_SYSCALL_INTERRUPT_PRIORITY - 2u);
}

void uart_transmit(char *str, uint8_t size)
{
  // Copy to buffer and cut buffer if too long
  uart_tx_size = size > UART_MAX_SIZE ? UART_MAX_SIZE : size;
  memcpy(uart_tx_buffer, str, uart_tx_size * sizeof(char));
  uart_tx_idx = 0u;
  uart_send_next_char();
}

void LPUART1_IRQHandler(void)
{
  if (LPUART1->ISR & USART_ISR_TC)
  {
    LPUART1->ICR |= USART_ICR_TCCF; // Clear interrupt
    uart_send_next_char();
  }
}

static void uart_send_next_char(void)
{
  LPUART1->TDR = uart_tx_buffer[uart_tx_idx];
  uart_tx_idx++;
  uart_tx_size--;
  if(uart_tx_size == 0u)
  {
    // full buffer has been sent
    LPUART1->CR1 &= ~USART_CR1_TCIE; // Disable TXE interrupt when done
  }
}
