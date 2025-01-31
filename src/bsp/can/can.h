#ifndef _CAN_H_
#define _CAN_H_

#include <stdint.h>

// Maximum payload is 8 bytes
#define CAN_MAX_PAYLOAD_SIZE (8u)

typedef struct
{
  uint32_t u32_extID;
  uint8_t u8_cmd;
  uint8_t u8_data[CAN_MAX_PAYLOAD_SIZE];
  uint8_t u8_length;
} Can_Data_t;

/**
  @brief Initialize FDCAN peripheral and driver.
 */
void can_init(void);

#endif // _CAN_H_