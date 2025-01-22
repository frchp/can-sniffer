#ifndef _WDOG_TASK_H_
#define _WDOG_TASK_H_

#include "FreeRTOS.h"
#include "task.h"

/* Motor task configuration */
#define WDOG_TASK_PRIORITY     (3u)
#define WDOG_TASK_STACK_SIZE   (128u)

extern TaskHandle_t WatchdogTaskHandle;
extern StackType_t gbl_sStackWdog[WDOG_TASK_STACK_SIZE];
extern StaticTask_t gbl_sTCBWdog;

void WatchdogTask(void *pvParameters);

#endif // _WDOG_TASK_H_
