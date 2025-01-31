#include <stdint.h>

#include "bsp.h"
#include "app.h"
#include "task_handler.h"
#include "error.h"

int main(void)
{
  bsp_init();

  app_init();

  task_init();
  task_startOS();

  /* OS is started now, we should not be here */
  Error_Handler(true, ERR_MAIN, ERR_TYPE_FAULT);
}
