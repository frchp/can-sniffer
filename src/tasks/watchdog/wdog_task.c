#include "wdog_task.h"

#include "watchdog.h"
#include "stm32l552xx.h"

/* Watchdog task parameters */
TaskHandle_t s_wdogTaskHdl;
StackType_t s_wdogTaskStack [WDOG_TASK_STACK_SIZE];
StaticTask_t s_wdogTaskTCB;

#define GPIO_LED_ALIVE_PORT       (GPIOA)
#define GPIO_LED_ALIVE_PIN        (GPIO_ODR_OD9)

void WatchdogTask(void *pv_param)
{
  (void)pv_param; // Avoid compiler warning for unused parameter

  for (;;)
  {
    // Block for 500 ms and refresh watchdog
    vTaskDelay(pdMS_TO_TICKS(500));
    if((GPIO_LED_ALIVE_PORT->ODR & GPIO_LED_ALIVE_PIN) != 0u)
    {
      // if LED was on, turn off
      GPIO_LED_ALIVE_PORT->ODR &= ~GPIO_LED_ALIVE_PIN;
    }
    else
    {
      // if LED was off, turn on
      GPIO_LED_ALIVE_PORT->ODR |= GPIO_LED_ALIVE_PIN;
    }
    watchdog_refresh();
  }
}
