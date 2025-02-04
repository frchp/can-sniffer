#ifndef _WDOG_TASK_H_
#define _WDOG_TASK_H_

#include "FreeRTOS.h"
#include "task.h"

/* Watchdog task configuration */
#define WDOG_TASK_PRIORITY     (2u)
#define WDOG_TASK_STACK_SIZE   (256u)

extern TaskHandle_t s_wdogTaskHdl;
extern StackType_t s_wdogTaskStack[WDOG_TASK_STACK_SIZE];
extern StaticTask_t s_wdogTaskTCB;

void WatchdogTask(void *pv_param);

#endif // _WDOG_TASK_H_
