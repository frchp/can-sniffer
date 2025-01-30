#include <stdint.h>

#include "bsp.h"
#include "app.h"
#include "task_handler.h"
#include "watchdog.h"

int main(void)
{
  bsp_init();

  app_init();

  // TaskHandler_Init();
  // TaskHandler_StartOS();

  /* OS is started now, we should not be here */
  while(1)
  {
    watchdog_refresh();
  }
}
