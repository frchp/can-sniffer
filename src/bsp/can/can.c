#include "can.h"

#include "stm32l552xx.h"
#include "uart.h"
#include <stdio.h> // TODO : to be moved

void can_init(void)
{
  RCC->APB1ENR1 |= RCC_APB1ENR2_FDCAN1EN;

  // Enable clock to FDCAN
  RCC->CCIPR1 |= (3U << RCC_CCIPR1_FDCANSEL_Pos);  // SYSCLK source

  // Enter initialization mode
  FDCAN1->CCCR |= FDCAN_CCCR_INIT;
  while (!(FDCAN1->CCCR & FDCAN_CCCR_INIT));

  // Configure nominal bit timing (Assuming 40MHz clock, 500 kbps CAN)
  FDCAN1->NBTP = (10U << 16) | (13U << 8) | (3U << 0);

  // Enable global filter to accept all messages
  FDCAN1->RXGFC = 0;

  // Enable RX FIFO 0 new message interrupt
  FDCAN1->IE |= FDCAN_IE_RF0NE;
  NVIC_EnableIRQ(FDCAN1_IT0_IRQn);

  // Exit initialization mode
  FDCAN1->CCCR &= ~FDCAN_CCCR_INIT;
  while (FDCAN1->CCCR & FDCAN_CCCR_INIT);
}

void FDCAN1_IT0_IRQHandler(void)
{
  if (FDCAN1->IR & FDCAN_IR_RF0N)
  {
    FDCAN1->IR = FDCAN_IR_RF0N;  // Clear interrupt flag

    if (FDCAN1->RXF0S & FDCAN_RXF0S_F0FL_Msk)
    {
      uint32_t get_index = (FDCAN1->RXF0S & FDCAN_RXF0S_F0GI_Msk) >> FDCAN_RXF0S_F0GI_Pos;
      // Check if FIFO has data
      uint32_t id = FDCAN1->RXF0A & 0x1FFFFFFF;
      uint32_t data = 0u; //= FDCAN1->RXF0D[0]; // TODO : data is handled otherwise

      /* TODO : send event and do this in other task */
      char msg[50];
      sprintf(msg, "CAN ID: 0x%lu, Data: 0x%lu\r\n", id, data);
      uart_transmit(msg, 50);

      FDCAN1->RXF0A = (FDCAN1->RXF0A & FDCAN_RXF0A_F0AI_Msk);  // Acknowledge message
    }
  }
}
