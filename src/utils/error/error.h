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
  ERR_MAIN,

  ERR_HARD,
  ERR_BUS,
  ERR_MEM,

  ERR_OS,
  ERR_OS_MEDIA_TASK,
  ERR_OS_WDOG_TASK,
  ERR_OS_HMI_TASK,

  ERR_OTHER
} Error_Component_t;

void Error_Handler(bool b_isCritical, Error_Component_t e_component, Error_Type_t e_type);

#endif // _ERROR_H_