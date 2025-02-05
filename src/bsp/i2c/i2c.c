#include "i2c.h"

#include "stm32l552xx.h"

#define I2C_TIMEOUT (10000ul)

/**
 * TODO : interrupt driven I2C + RX/TX state
 * IDLE
 * RX_REG
 * RX_DATA (stay in for burst, out for normal)
 * TX_REG
 * TX_DATA (stay in for burst, out for normal)
 * Interrupts : i2c_ER_IRQHandler (errors) i2c_EV_IRQHandler (transfer rx/tx)
 *
 * TODO : initialize GPIO for I2C1
 */

void i2c_Init(void)
{
  RCC->APB1ENR1 |= RCC_APB1ENR1_I2C1EN; // Enable I2C1 clock
  RCC->CCIPR1 &= ~RCC_CCIPR1_I2C1SEL; // Use PCLK as I2C clock source

  I2C1->CR1 &= ~I2C_CR1_PE; // Disable I2C before configuration
  I2C1->TIMINGR = 0x00303D5B; // Configure timing (adjust as needed)
  I2C1->CR1 |= I2C_CR1_PE; // Enable I2C
}

int i2c_Write(uint8_t addr, uint8_t reg, uint8_t data)
{
  I2C1->CR2 = (addr << 1) | (1 << 16) | I2C_CR2_START;

  while (!(I2C1->ISR & I2C_ISR_TXIS));
  I2C1->TXDR = reg;

  while (!(I2C1->ISR & I2C_ISR_TXIS));
  I2C1->TXDR = data;

  while (!(I2C1->ISR & I2C_ISR_TC));
  I2C1->CR2 |= I2C_CR2_STOP;

  return NO_ERROR;
}

int i2c_Read(uint8_t addr, uint8_t reg, uint8_t *data)
{
  I2C1->CR2 = (addr << 1) | (1 << 16) | I2C_CR2_START;
  while (!(I2C1->ISR & I2C_ISR_TXIS));

  I2C1->TXDR = reg;
  while (!(I2C1->ISR & I2C_ISR_TC));

  I2C1->CR2 = (addr << 1) | (1 << 16) | I2C_CR2_RD_WRN | I2C_CR2_START;
  while (!(I2C1->ISR & I2C_ISR_RXNE));
  *data = I2C1->RXDR;

  I2C1->CR2 |= I2C_CR2_STOP;
  return NO_ERROR;
}

int i2c_WriteBurst(uint8_t addr, uint8_t reg, uint8_t *data, uint8_t len)
{
  I2C1->CR2 = (addr << 1) | ((len + 1) << 16) | I2C_CR2_START;

  while (!(I2C1->ISR & I2C_ISR_TXIS));
  I2C1->TXDR = reg;

  for (uint8_t i = 0; i < len; i++)
  {
    while (!(I2C1->ISR & I2C_ISR_TXIS));
    I2C1->TXDR = data[i];
  }

  while (!(I2C1->ISR & I2C_ISR_TC));
  I2C1->CR2 |= I2C_CR2_STOP;

  return NO_ERROR;
}

int i2c_ReadBurst(uint8_t addr, uint8_t reg, uint8_t *data, uint8_t len)
{
  I2C1->CR2 = (addr << 1) | (1 << 16) | I2C_CR2_START;
  while (!(I2C1->ISR & I2C_ISR_TXIS));

  I2C1->TXDR = reg;
  while (!(I2C1->ISR & I2C_ISR_TC));

  I2C1->CR2 = (addr << 1) | (len << 16) | I2C_CR2_RD_WRN | I2C_CR2_START;
  for (uint8_t i = 0; i < len; i++)
  {
    while (!(I2C1->ISR & I2C_ISR_RXNE));
    data[i] = I2C1->RXDR;
  }

  I2C1->CR2 |= I2C_CR2_STOP;
  return NO_ERROR;
}
