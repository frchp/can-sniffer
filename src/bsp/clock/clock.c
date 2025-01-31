#include "clock.h"

#include "stm32l552xx.h"
#include "board.h"

/**
  @brief Initialize clock tree.
 */
void clock_init(void)
{
  // Enable MCO (assumed to be at 8MHz)
  #ifdef USE_ST_NUCLEO
    RCC->CFGR |= (1U << RCC_CFGR_MCOSEL_Pos); // Select MSI as MCO source (Default 8MHz)

    // Configure PLL: Source = MCO (8 MHz), Output = 110 MHz
    RCC->PLLCFGR = (2U << RCC_PLLCFGR_PLLSRC_Pos)  // MCO as PLL source
                  | (55U << RCC_PLLCFGR_PLLN_Pos)  // Multiply by 55
                  | (2U << RCC_PLLCFGR_PLLM_Pos)   // Divide by 2
                  | (1U << RCC_PLLCFGR_PLLREN_Pos); // Enable PLLR output
  #else
    // Enable HSE (External Clock)
    RCC->CR |= RCC_CR_HSEON;
    while (!(RCC->CR & RCC_CR_HSERDY));

    // Configure PLL: Source = HSE (8 MHz), Output = 110 MHz
    RCC->PLLCFGR = (1U << RCC_PLLCFGR_PLLSRC_Pos)  // HSE as PLL source
                  | (55U << RCC_PLLCFGR_PLLN_Pos)  // Multiply by 55
                  | (1U << RCC_PLLCFGR_PLLM_Pos)   // Divide by 1
                  | (1U << RCC_PLLCFGR_PLLREN_Pos); // Enable PLLR output
  #endif

  // Enable PLL
  RCC->CR |= RCC_CR_PLLON;
  while (!(RCC->CR & RCC_CR_PLLRDY));

  // Select PLL as system clock
  RCC->CFGR |= (3U << RCC_CFGR_SW_Pos);
  while ((RCC->CFGR & RCC_CFGR_SWS_Msk) != (3U << RCC_CFGR_SWS_Pos));
}