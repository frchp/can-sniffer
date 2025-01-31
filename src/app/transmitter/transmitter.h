#ifndef _TRANSMITTER_H_
#define _TRANSMITTER_H_

#include <stdint.h>
#include "can.h"

/**
  @brief Serialize can data into ASCII characters to send to User.
 */
void transmitter_serialize(Can_Data_t s_canData, char* ac_outBuff, const uint8_t u8_maxSize);

#endif // _TRANSMITTER_H_