#include "watchdog.h"

#include "stm32l552xx.h"

void watchdog_init(void)
{
  // Enable independent watchdog (IWDG)
  IWDG->KR = 0xCCCC; // Start the watchdog
  IWDG->KR = 0x5555; // Enable register access
  /**
  * T = (4 * 2^PR * RLD / f_LSI)
  * so T = 8s with PR = 4 and RLD = 0xFFF, f_LSI = 32kHz
  */
  IWDG->PR = 0x04;   // Set prescaler
  IWDG->RLR = 0xFFF; // Reload value
  while(IWDG->SR != 0ul);
  IWDG->KR = 0xAAAA; // Reload counter
}

void watchdog_refresh(void)
{
  IWDG->KR = 0xAAAA; // Refresh watchdog counter
}
