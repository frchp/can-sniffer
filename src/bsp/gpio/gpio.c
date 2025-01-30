#include "gpio.h"

#include "stm32l552xx.h"

void gpio_init(void)
{
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN | RCC_AHB2ENR_GPIOBEN;

  // Configure PB8 as CAN1_RX and PB9 as CAN1_TX (AF9)
  GPIOB->MODER &= ~(GPIO_MODER_MODE8 | GPIO_MODER_MODE9);
  GPIOB->MODER |= (2U << GPIO_MODER_MODE8_Pos) | (2U << GPIO_MODER_MODE9_Pos);
  GPIOB->AFR[1] |= (9U << GPIO_AFRH_AFSEL8_Pos) | (9U << GPIO_AFRH_AFSEL9_Pos);

  // Configure PA2 as LPUART1_TX (AF8)
  GPIOA->MODER &= ~GPIO_MODER_MODE2;
  GPIOA->MODER |= (2U << GPIO_MODER_MODE2_Pos);
  GPIOA->AFR[0] |= (8U << GPIO_AFRL_AFSEL2_Pos);
}
