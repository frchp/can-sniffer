#include <stddef.h>

#include "task_handler.h"

#include "FreeRTOS.h"
#include "task.h"
#include "FreeRTOSConfig.h"

#include "error.h"
#include "media_task.h"
#include "wdog_task.h"
#include "idle_task.h"
#include "board.h"

#define OS_TASK_MAX_PRIO (configMAX_PRIORITIES - 1)

/**
  @brief Setup OS tasks.
 */
void task_init(void)
{
  /**
   * Highest priority
   * Media -> IDLE + 2
   * Watchdog -> IDLE + 1
   * Lowest priority = IDLE
   */
  // Create MEDIA Task
  s_mediaTaskHdl = xTaskCreateStatic(MediaTask,            // Task function
              "MEDIA",              // Task name
              MEDIA_TASK_STACK_SIZE,                  // Stack size in words
              NULL,                 // Task parameter
              OS_TASK_MAX_PRIO - MEDIA_TASK_PRIORITY, // Task priority
              s_mediaTaskStack,
              &s_mediaTaskTCB );
  if(s_mediaTaskHdl == NULL)
  {
    Error_Handler(true, ERR_OS_MEDIA_TASK, ERR_TYPE_INIT);
  }

  // Create WATCHDOG Task
  s_wdogTaskHdl = xTaskCreateStatic(WatchdogTask,            // Task function
              "WATCHDOG",             // Task name
              WDOG_TASK_STACK_SIZE,                         // Stack size in words
              NULL,                        // Task parameter
              OS_TASK_MAX_PRIO - WDOG_TASK_PRIORITY,        // Task priority
              s_wdogTaskStack,
              &s_wdogTaskTCB );
  if(s_wdogTaskHdl == NULL)
  {
    Error_Handler(true, ERR_OS_WDOG_TASK, ERR_TYPE_INIT);
  }
}

/**
  @brief Start OS.
 */
void task_startOS(void)
{
  // Start the FreeRTOS Scheduler
  vTaskStartScheduler();
}

/**
  @brief Provide the memory used by the Idle task
*/
#if (configSUPPORT_STATIC_ALLOCATION == 1)
static StaticTask_t xIdleTaskTCB;
static StackType_t uxIdleTaskStack[ configMINIMAL_STACK_SIZE ];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer,
                                    StackType_t **ppxIdleTaskStackBuffer,
                                    uint32_t *pulIdleTaskStackSize )
{
  /* Pass out a pointer to the StaticTask_t structure in which the Idle task's
      state will be stored. */
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCB;

  /* Pass out the array that will be used as the Idle task's stack. */
  *ppxIdleTaskStackBuffer = uxIdleTaskStack;

  /* Pass out the size of the array pointed to by *ppxIdleTaskStackBuffer.
      Note that, as the array is necessarily of type StackType_t,
      configMINIMAL_STACK_SIZE is specified in words, not bytes. */
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}

/**
  @brief Provide the memory used by the Timer service task
*/
#if (configUSE_TIMERS == 1)
static StaticTask_t xTimerTaskTCB;
static StackType_t uxTimerTaskStack[ configTIMER_TASK_STACK_DEPTH ];

void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer,
                                     StackType_t **ppxTimerTaskStackBuffer,
                                     uint32_t *pulTimerTaskStackSize )
{
  /* Pass out a pointer to the StaticTask_t structure in which the Timer
      task's state will be stored. */
  *ppxTimerTaskTCBBuffer = &xTimerTaskTCB;

  /* Pass out the array that will be used as the Timer task's stack. */
  *ppxTimerTaskStackBuffer = uxTimerTaskStack;

  /* Pass out the size of the array pointed to by *ppxTimerTaskStackBuffer.
      Note that, as the array is necessarily of type StackType_t,
    configTIMER_TASK_STACK_DEPTH is specified in words, not bytes. */
  *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
}
#endif // (configUSE_TIMERS == 1)
#endif // (configSUPPORT_STATIC_ALLOCATION == 1)

#if (configCHECK_FOR_STACK_OVERFLOW == 2)
void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName)
{
  while (1);
}
#endif // (configCHECK_FOR_STACK_OVERFLOW == 2)