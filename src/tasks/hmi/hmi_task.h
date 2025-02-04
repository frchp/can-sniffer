#ifndef _HMI_TASK_H_
#define _HMI_TASK_H_

#include <stdint.h>
#include "FreeRTOS.h"
#include "task.h"

/* HMI task configuration */
#define HMI_TASK_PRIORITY     (3u)
#define HMI_TASK_STACK_SIZE   (128u)

extern TaskHandle_t s_hmiTaskHdl;
extern StackType_t s_hmiTaskStack[HMI_TASK_STACK_SIZE];
extern StaticTask_t s_hmiTaskTCB;

/* Events */
#define HMI_START_PROCESSING       (1u << 0u)
#define HMI_STOP_PROCESSING        (1u << 1u)
#define HMI_IS_ALIVE               (1u << 2u)

void HmiTask_Notify(uint32_t arg_u32Evt);

void HmiTask(void *pv_param);

#endif // _HMI_TASK_H_
