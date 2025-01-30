#include <stdbool.h>
#include <stddef.h>

#include "media_task.h"

#include "error.h"
#include "can.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/* Media task parameters*/
TaskHandle_t gbl_sMediaTaskHandle;
StackType_t gbl_sStackMedia [MEDIA_TASK_STACK_SIZE];
StaticTask_t gbl_sTCBMedia;

#define CANDATA_QUEUE_LENGTH            5u
#define CANDATA_QUEUE_ITEM_SIZE         sizeof( Can_Data_t )
static StaticQueue_t gbl_sCanDataQueue;
static uint8_t gbl_au8CanDataQueueStorage[ CANDATA_QUEUE_LENGTH * CANDATA_QUEUE_ITEM_SIZE ];
static QueueHandle_t gbl_sCanDataQueueHdl;

static bool gbl_bTaskInitialized = false;

void MediaTask_OnReception(void *can_data)
{
  BaseType_t xHigherPriorityTaskWoken = pdFALSE;
  if(gbl_bTaskInitialized)
  {
    if(xPortIsInsideInterrupt() != 0u)
    {
      // In interrupt context
      xQueueSendToBackFromISR(gbl_sCanDataQueueHdl,
                    can_data,
                    &xHigherPriorityTaskWoken);
      vTaskNotifyGiveFromISR(gbl_sMediaTaskHandle, &xHigherPriorityTaskWoken);
      portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
    }
    else
    {
      xQueueSendToBack(gbl_sCanDataQueueHdl,
                    can_data,
                    0u);
      xTaskNotifyGive(gbl_sMediaTaskHandle);
    }
  }
}

void MediaTask(void *arg_pvParameters)
{
  (void)arg_pvParameters; // Avoid compiler warning for unused parameter
  uint32_t u32NotifiedValue;

  gbl_sCanDataQueueHdl = xQueueCreateStatic( CANDATA_QUEUE_LENGTH,
                                 CANDATA_QUEUE_ITEM_SIZE,
                                 gbl_au8CanDataQueueStorage,
                                 &gbl_sCanDataQueue );
  if(gbl_sCanDataQueueHdl == NULL)
  {
    Error_Handler(true, ERR_OS_MEDIA_TASK, ERR_TYPE_INIT);
  }
  gbl_bTaskInitialized = true;

  for (;;)
  {
    // Notification is used as counting semaphore for order_handler incoming
    u32NotifiedValue = ulTaskNotifyTake( pdFALSE /* value decremented */,
                                        portMAX_DELAY /* wait for ever for an incoming msg */);

    if( u32NotifiedValue > 0u )
    {
      // TODO : use queue to get data from CAN peripheral
      // TODO : call application to set data correctly
      // TODO : call UART to send data
    }
    else
    {
      // OS error if we are here
      Error_Handler(true, ERR_OS_MEDIA_TASK, ERR_TYPE_TIMEOUT);
    }
  }
}
