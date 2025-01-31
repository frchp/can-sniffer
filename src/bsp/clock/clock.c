#include "clock.h"

#include "stm32l552xx.h"
#include "board.h"

/**
  @brief Initialize clock tree.
 */
void clock_init(void)
{
  RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
  RCC->APB1ENR1 |= RCC_APB1ENR1_PWREN;

  RCC->CSR |= RCC_CSR_LSION;
  while (!(RCC->CR & RCC_CSR_LSIRDY));

  #ifdef USE_ST_NUCLEO
  // Enable MSI (assumed to be at 8MHz)
  RCC->CR |= RCC_CR_MSION;
  while (!(RCC->CR & RCC_CR_MSIRDY));

  RCC->CR |= RCC_CR_MSIRGSEL;
  // Clear and set range to 8MHz
  RCC->CR &= ~RCC_CR_MSIRANGE_Msk;
  RCC->CR |= (RCC_CR_MSIRANGE_2 | RCC_CR_MSIRANGE_1);

  RCC->CFGR &= ~ RCC_CFGR_MCOSEL; // No clock on MCO output

  // Configure PLL: Source = MSI (8 MHz), Output = 110 MHz
  RCC->PLLCFGR = (RCC_PLLCFGR_PLLSRC_0)  // MSI as PLL source
                | (55U << RCC_PLLCFGR_PLLN_Pos)  // Multiply by 55
                | (2U << RCC_PLLCFGR_PLLM_Pos)   // Divide by 2
                | (0U << RCC_PLLCFGR_PLLR_Pos);
  #else
  // Enable HSE (External Clock)
  RCC->CR |= RCC_CR_HSEON;
  while (!(RCC->CR & RCC_CR_HSERDY));

  // Configure PLL: Source = HSE (8 MHz), Output = 110 MHz
  RCC->PLLCFGR = (RCC_PLLCFGR_PLLSRC)  // HSE as PLL source
                | (55U << RCC_PLLCFGR_PLLN_Pos)  // Multiply by 55
                | (2U << RCC_PLLCFGR_PLLM_Pos)   // Divide by 2
                | (0U << RCC_PLLCFGR_PLLR_Pos);
  #endif

  // Enable PLL
  RCC->CR |= RCC_CR_PLLON;
  RCC->PLLCFGR |= RCC_PLLCFGR_PLLREN; // Enable PLLR output
  while (!(RCC->CR & RCC_CR_PLLRDY));

  // Select PLL as system clock
  RCC->CFGR |= RCC_CFGR_SW;
  while ((RCC->CFGR & RCC_CFGR_SWS_Msk) != RCC_CFGR_SWS);
}