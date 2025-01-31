#include "mcp2551.h"

#include "stm32l552xx.h"

#define GPIO_MCP_RS_PORT       (GPIOD)
#define GPIO_MCP_RS_PIN        (GPIO_ODR_OD5)

/**
  @brief Put the driver in Standby mode.
 */
void mcp2551_StandbyMode(void)
{
  // Driver is in standby when Rs pin is reset
  GPIO_MCP_RS_PORT->ODR &= ~GPIO_MCP_RS_PIN;
}

/**
  @brief Put the driver in High speed mode.
 */
void mcp2551_HighSpeedMode(void)
{
  // Driver is in standby when Rs pin is set
  GPIO_MCP_RS_PORT->ODR |= GPIO_MCP_RS_PIN;
}
