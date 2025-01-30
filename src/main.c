#include <stdint.h>

#include "bsp.h"
#include "app.h"
#include "task_handler.h"

int main(void)
{
  bsp_init();

  app_init();

  task_init();
  task_startOS();

  /* OS is started now, we should not be here */
}
