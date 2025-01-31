#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#include "media_task.h"

#include "error.h"
#include "can.h"
#include "transmitter.h"
#include "uart.h"

#include "queue.h"

/* Media task parameters*/
TaskHandle_t s_mediaTaskHdl;
StackType_t s_mediaTaskStack [MEDIA_TASK_STACK_SIZE];
StaticTask_t s_mediaTaskTCB;

#define CANDATA_QUEUE_LENGTH            5u
#define CANDATA_QUEUE_ITEM_SIZE         sizeof( Can_Data_t )
static StaticQueue_t s_canDataQueue;
static uint8_t au8_canDataQueueBuff[ CANDATA_QUEUE_LENGTH * CANDATA_QUEUE_ITEM_SIZE ];
static QueueHandle_t s_canDataQueueHdl;

#define MEDIA_MAX_TRANSMIT_SIZE (120u)

static bool b_taskInit = false;

void MediaTask_OnReception(void *pv_canData)
{
  BaseType_t xHigherPriorityTaskWoken = pdFALSE;
  if(b_taskInit)
  {
    if(xPortIsInsideInterrupt() != 0u)
    {
      // In interrupt context
      xQueueSendToBackFromISR(s_canDataQueueHdl,
                    pv_canData,
                    &xHigherPriorityTaskWoken);
      vTaskNotifyGiveFromISR(s_mediaTaskHdl, &xHigherPriorityTaskWoken);
      portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
    }
    else
    {
      xQueueSendToBack(s_canDataQueueHdl,
                    pv_canData,
                    0u);
      xTaskNotifyGive(s_mediaTaskHdl);
    }
  }
}

void MediaTask(void *pv_param)
{
  (void)pv_param; // Avoid compiler warning for unused parameter
  uint32_t u32NotifiedValue;
  Can_Data_t s_incomingCanData;
  char ac_transmitBuff[MEDIA_MAX_TRANSMIT_SIZE];

  s_canDataQueueHdl = xQueueCreateStatic( CANDATA_QUEUE_LENGTH,
                                 CANDATA_QUEUE_ITEM_SIZE,
                                 au8_canDataQueueBuff,
                                 &s_canDataQueue );
  if(s_canDataQueueHdl == NULL)
  {
    Error_Handler(true, ERR_OS_MEDIA_TASK, ERR_TYPE_INIT);
  }
  b_taskInit = true;

  for (;;)
  {
    // Notification is used as counting semaphore for order_handler incoming
    u32NotifiedValue = ulTaskNotifyTake( pdFALSE /* value decremented */,
                                        portMAX_DELAY /* wait for ever for an incoming msg */);

    if( u32NotifiedValue > 0u )
    {
      if(xQueueReceive(s_canDataQueueHdl, &s_incomingCanData, 0u) == pdPASS)
      {
        transmitter_serialize(s_incomingCanData, ac_transmitBuff, MEDIA_MAX_TRANSMIT_SIZE);
        uart_transmit(ac_transmitBuff, strlen(ac_transmitBuff));
      }
    }
    else
    {
      // OS error if we are here
      Error_Handler(true, ERR_OS_MEDIA_TASK, ERR_TYPE_TIMEOUT);
    }
  }
}
