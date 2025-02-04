#include <stdint.h>

#include "hmi_task.h"
#include "hmi.h"
#include "error.h"

/* HMI task parameters */
TaskHandle_t s_hmiTaskHdl;
StackType_t s_hmiTaskStack[HMI_TASK_STACK_SIZE];
StaticTask_t s_hmiTaskTCB;

static bool b_taskInit = false;

void HmiTask_Notify(uint32_t arg_u32Evt)
{
  BaseType_t xHigherPriorityTaskWoken = pdFALSE;
  if(b_taskInit)
  {
    if(xPortIsInsideInterrupt() != 0u)
    {
        // In interrupt context
        xTaskNotifyFromISR( s_hmiTaskHdl,
                        arg_u32Evt,
                        eSetBits,
                        &xHigherPriorityTaskWoken );
        portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
    }
    else
    {
        xTaskNotify( s_hmiTaskHdl,
                    arg_u32Evt,
                    eSetBits );
    }
  }
}

void HmiTask(void *pv_param)
{
  (void)pv_param; // Avoid compiler warning for unused parameter
  uint32_t u32_notifiedValue = 0ul;
  uint32_t u32_status;

  b_taskInit = true;

  for (;;)
  {
    u32_status = xTaskNotifyWait( pdFALSE,          /* Don't clear bits on entry. */
                                 UINT32_MAX,        /* Clear all bits on exit. */
                                 &u32_notifiedValue, /* Stores the notified value. */
                                 portMAX_DELAY );

    if( u32_status == pdPASS )
    {
      if( ( u32_notifiedValue & HMI_START_PROCESSING ) != 0 )
      {
        hmi_startProcessing();
      }

      if( ( u32_notifiedValue & HMI_STOP_PROCESSING ) != 0 )
      {
        hmi_stopProcessing();
      }

      if( ( u32_notifiedValue & HMI_IS_ALIVE ) != 0 )
      {
        hmi_isAlive();
      }
    }
    else
    {
      // OS error if we are here
      Error_Handler(true, ERR_OS_HMI_TASK, ERR_TYPE_TIMEOUT);
    }
  }
}
