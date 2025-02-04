#include "gpio.h"

#include "stm32l552xx.h"

/**
  @brief Initialize project GPIO.
 */
void gpio_init(void)
{
  RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN | RCC_AHB2ENR_GPIOBEN | RCC_AHB2ENR_GPIODEN;

  // Configure PB8 as CAN1_RX and PB9 as CAN1_TX (AF9)
  GPIOB->MODER &= ~(GPIO_MODER_MODE8 | GPIO_MODER_MODE9);
  GPIOB->MODER |= (2U << GPIO_MODER_MODE8_Pos) | (2U << GPIO_MODER_MODE9_Pos);
  GPIOB->AFR[1] |= (9U << GPIO_AFRH_AFSEL8_Pos) | (9U << GPIO_AFRH_AFSEL9_Pos);

  // Configure PA2 as LPUART1_TX (AF8)
  GPIOA->MODER &= ~GPIO_MODER_MODE2;
  GPIOA->MODER |= (2U << GPIO_MODER_MODE2_Pos);
  GPIOA->AFR[0] |= (8U << GPIO_AFRL_AFSEL2_Pos);

  // Configure PD5 as general output pin (MCP2551)
  GPIOD->MODER &= ~GPIO_MODER_MODE5;
  GPIOD->MODER |= 1U << GPIO_MODER_MODE5_Pos;
  GPIOD->OTYPER &= ~GPIO_OTYPER_OT5; // Push-pull mode
  GPIOD->OSPEEDR |= 3U << GPIO_OSPEEDR_OSPEED5_Pos; // High speed
  GPIOD->PUPDR &= ~GPIO_PUPDR_PUPD5; // No pull-up/down

  // Configure PA9 as general output pin (Alive LED)
  GPIOA->MODER &= ~GPIO_MODER_MODE9;
  GPIOA->MODER |= 1U << GPIO_MODER_MODE9_Pos;
  GPIOA->OTYPER &= ~GPIO_OTYPER_OT9; // Push-pull mode
  GPIOA->OSPEEDR |= 3U << GPIO_OSPEEDR_OSPEED9_Pos; // High speed
  GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD9; // No pull-up/down

  // Configure PB7 as general output pin (RX - Processing LED)
  GPIOB->MODER &= ~GPIO_MODER_MODE7;
  GPIOB->MODER |= 1U << GPIO_MODER_MODE7_Pos;
  GPIOB->OTYPER &= ~GPIO_OTYPER_OT7; // Push-pull mode
  GPIOB->OSPEEDR |= 3U << GPIO_OSPEEDR_OSPEED7_Pos; // High speed
  GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD7; // No pull-up/down
}
