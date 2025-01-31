#include "can.h"

#include "stm32l552xx.h"
#include "uart.h"
#include "FreeRTOSConfig.h"
#include <stdio.h> // TODO : to be moved
#include <string.h>
#include "media_task.h"

static volatile Can_Data_t s_can_data_rx;

/**
  @brief Initialize FDCAN peripheral and driver.
 */
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
  NVIC_SetPriority(FDCAN1_IT0_IRQn, configMAX_SYSCALL_INTERRUPT_PRIORITY - 1u);

  // Exit initialization mode
  FDCAN1->CCCR &= ~FDCAN_CCCR_INIT;
  while (FDCAN1->CCCR & FDCAN_CCCR_INIT);
}

/**
  @brief Interrupt routine.
 */
void FDCAN1_IT0_IRQHandler(void)
{
  if (FDCAN1->IR & FDCAN_IR_RF0N)
  {
    FDCAN1->IR = FDCAN_IR_RF0N;  // Clear interrupt flag

    if (FDCAN1->RXF0S & FDCAN_RXF0S_F0FL_Msk)
    {
      uint32_t get_index = (FDCAN1->RXF0S & FDCAN_RXF0S_F0GI_Msk) >> FDCAN_RXF0S_F0GI_Pos;
      uint32_t *rx_fifo_address = (uint32_t *)(FDCAN1_BASE + 0x100 + (get_index * 0x10));

      s_can_data_rx.u32_extID = (rx_fifo_address[0] >> 3) & 0x1FFFFFFF;
      s_can_data_rx.u8_length = (rx_fifo_address[1] & 0xF);

      for (uint8_t i = 0; i < s_can_data_rx.u8_length; i++)
      {
        s_can_data_rx.u8_data[i] = ((uint8_t*)&rx_fifo_address[2])[i];
      }

      FDCAN1->RXF0A = get_index; // Acknowledge message

      MediaTask_OnReception((void *)&s_can_data_rx);
      /* TODO : send event and do this in other task */
      char msg[50];
      sprintf(msg, "CAN ID: 0x%08lu, Data: ", s_can_data_rx.u32_extID);
      for (uint8_t i = 0; i < s_can_data_rx.u8_length; i++) {
          sprintf(msg + strlen(msg), "%02X ", s_can_data_rx.u8_data[i]);
      }
      strcat(msg, "\r\n");
      uart_transmit(msg, 50);
    }
  }
}
