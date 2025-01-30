#include "bsp.h"

#include "can.h"
#include "gpio.h"
#include "uart.h"
#include "watchdog.h"

/**
  @brief Setup the BSP.
 */
void bsp_init (void)
{
  gpio_init();
  can_init();
  uart_init();
  watchdog_init();
}

void SystemInit (void)
{
#if defined(USER_VECT_TAB_ADDRESS)
  SCB->VTOR = VECT_TAB_BASE_ADDRESS | VECT_TAB_OFFSET;
#endif

#if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
  SCB->CPACR |= ((3UL << 20U)|(3UL << 22U));  /* set CP10 and CP11 Full Access */
#endif
}
