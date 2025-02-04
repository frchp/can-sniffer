#include "app.h"

#include "mcp2551.h"
#include "hmi.h"

/**
  @brief Setup the application.
 */
void app_init(void)
{
  mcp2551_HighSpeedMode(); // state by default
  hmi_stopProcessing(); // state by default
}
