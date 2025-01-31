#ifndef _MEDIA_TASK_H_
#define _MEDIA_TASK_H_

#include "FreeRTOS.h"
#include "task.h"

/* Media task configuration */
#define MEDIA_TASK_PRIORITY     (1u)
#define MEDIA_TASK_STACK_SIZE   (512u)

extern TaskHandle_t s_mediaTaskHdl;
extern StackType_t s_mediaTaskStack[MEDIA_TASK_STACK_SIZE];
extern StaticTask_t s_mediaTaskTCB;

void MediaTask_OnReception(void *pv_canData);

void MediaTask(void *pv_param);

#endif // _MEDIA_TASK_H_
