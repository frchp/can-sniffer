#ifndef _CAN_H_
#define _CAN_H_

#include <stdint.h>

typedef struct
{
  /* TODO */
  uint8_t u8Data;
} Can_Data_t;

/**
  @brief Initialize FDCAN peripheral and driver.
 */
void can_init(void);

#endif // _CAN_H_