#include "uart.h"
#include "uart_config.h"

#include "stm32l552xx.h"
#include <stddef.h>
#include "FreeRTOSConfig.h"
#include <string.h> // memcpy

static char ac_uart_tx_buffer[UART_MAX_SIZE];
static volatile uint8_t u8_uart_tx_size = 0u;
static volatile uint8_t u8_uart_tx_idx = 0u;
static fpUartCallback fp_txCallback = NULL;

/* Private functions */
// Called after a character has been successfully sent
static void uart_prv_sendNextChar(void);

// Called after all characters have been sent
static void uart_prv_txComplete(void);

/**
  @brief Initialize LPUART1 peripheral and driver.
 */
void uart_init(void)
{
  RCC->APB1ENR2 |= RCC_APB1ENR2_LPUART1EN;
  // Configure baud rate (Assuming 80MHz clock, 115200 baud)
  LPUART1->BRR = 6944;
  LPUART1->CR1 |= USART_CR1_TE | USART_CR1_UE | USART_CR1_TCIE;
  NVIC_EnableIRQ(LPUART1_IRQn);
  NVIC_SetPriority(LPUART1_IRQn, configMAX_SYSCALL_INTERRUPT_PRIORITY - 1u);
}

/**
  @brief Add listener for end of transmission.
 */
void uart_attach(fpUartCallback fp_listener)
{
  if(fp_listener != NULL)
  {
    fp_txCallback = fp_listener;
  }
}

/**
  @brief Transmit given string.
 */
void uart_transmit(char *ac_str, uint8_t u8_size)
{
  // Copy to buffer and cut buffer if too long
  u8_uart_tx_size = u8_size > UART_MAX_SIZE ? UART_MAX_SIZE : u8_size;
  memcpy(ac_uart_tx_buffer, ac_str, u8_uart_tx_size * sizeof(char));
  u8_uart_tx_idx = 0u;
  uart_prv_sendNextChar();
}

/**
  @brief IRQ routine.
 */
void LPUART1_IRQHandler(void)
{
  if (LPUART1->ISR & USART_ISR_TC)
  {
    LPUART1->ICR |= USART_ICR_TCCF; // Clear interrupt
    uart_prv_sendNextChar();
  }
}

/**
  @brief Called after a character has been successfully sent.
 */
static void uart_prv_sendNextChar(void)
{
  LPUART1->TDR = ac_uart_tx_buffer[u8_uart_tx_idx];
  u8_uart_tx_idx++;
  u8_uart_tx_size--;
  if(u8_uart_tx_size == 0u)
  {
    // full buffer has been sent
    LPUART1->CR1 &= ~USART_CR1_TCIE; // Disable TXE interrupt when done
    uart_prv_txComplete();
  }
}

/**
  @brief Called after all characters have been sent
 */
static void uart_prv_txComplete(void)
{
  if(fp_txCallback != NULL)
  {
    fp_txCallback();
  }
}
