#include "hmi.h"

#include "stm32l552xx.h"

/* LED for HMI */
#define GPIO_LED_ALIVE_PORT            (GPIOA)
#define GPIO_LED_ALIVE_PIN             (GPIO_ODR_OD9)

#define GPIO_LED_PROCESSING_PORT       (GPIOB)
#define GPIO_LED_PROCESSING_PIN        (GPIO_ODR_OD7)


/**
  @brief Update human machine interface when processing starts.
 */
void hmi_startProcessing(void)
{
  // Turn on LED
  GPIO_LED_PROCESSING_PORT->ODR |= GPIO_LED_PROCESSING_PIN;
}

/**
  @brief Update human machine interface when processing stops.
 */
void hmi_stopProcessing(void)
{
  // Turn off LED
  GPIO_LED_PROCESSING_PORT->ODR &= ~GPIO_LED_PROCESSING_PIN;
}

/**
  @brief Update human machine interface as program is alive.
 */
void hmi_isAlive(void)
{
  // Toggle LED
  GPIO_LED_ALIVE_PORT->ODR ^= GPIO_LED_ALIVE_PIN;
}