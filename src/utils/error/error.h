#ifndef _ERROR_H_
#define _ERROR_H_

#include <stdint.h>
#include <stdbool.h>

typedef enum
{
  ERR_TYPE_IRQ,
  ERR_TYPE_DEFAULT,
  ERR_TYPE_INIT,
  ERR_TYPE_TIMEOUT,
  ERR_TYPE_OVERFLOW,
  ERR_TYPE_FAULT,
  ERR_TYPE_SAVE
} Error_Type_t;

typedef enum
{
  /* TODO : Add CAN sniffer errors codes */
  ERR_OTHER
} Error_Component_t;

void Error_Handler(bool arg_bIsCritical, Error_Component_t arg_eComponent, Error_Type_t arg_eType);

#endif // _ERROR_H_