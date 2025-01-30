#include "watchdog.h"

#include "stm32l552xx.h"

void watchdog_init(void)
{
  // Enable independent watchdog (IWDG)
  IWDG->KR = 0xCCCC; // Start the watchdog
  IWDG->KR = 0x5555; // Enable register access
  IWDG->PR = 0x06;   // Set prescaler (4s timeout with 32kHz LSI)
  IWDG->RLR = 0xFFF; // Reload value
  IWDG->KR = 0xAAAA; // Reload counter
}

void watchdog_refresh(void)
{
  IWDG->KR = 0xAAAA; // Refresh watchdog counter
}
