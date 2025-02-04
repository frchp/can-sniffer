#include "transmitter.h"

#include <stdio.h> // sprintf
#include <string.h> // strlen
#include "hmi_task.h"

/**
  @brief Serialize can data into ASCII characters to send to User.
 */
void transmitter_serialize(Can_Data_t s_canData, char* ac_outBuff, const uint8_t u8_maxSize)
{
  char ac_msg[u8_maxSize];
  sprintf(ac_msg, "CAN ID: 0x%08lu, Length: %d, Data: ", s_canData.u32_extID, s_canData.u8_length);
  for (uint8_t i = 0; (i < s_canData.u8_length) && (strlen(ac_msg) < u8_maxSize); i++) {
    sprintf(ac_msg + strlen(ac_msg), "%02X ", s_canData.u8_data[i]);
  }
}

/**
  @brief Callback when transmission is complete.
 */
void transmitter_isDone(void)
{
  HmiTask_Notify(HMI_STOP_PROCESSING);
}
