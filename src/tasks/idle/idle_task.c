#include "idle_task.h"

#include "mcp2551.h"
#include "FreeRTOSConfig.h"

#if configUSE_IDLE_HOOK == 1
  #pragma message "User defined idle hook enabled"
#endif

#if configUSE_TICKLESS_IDLE == 0
  #pragma message "Tickless idle disabled"
#endif

#if configUSE_TICKLESS_IDLE == 1
  #pragma message "FreeRTOS tickless idle enabled"
#endif

#if configUSE_TICKLESS_IDLE > 1
  #pragma message "User defined tickless idle enabled"
#endif

/**
  @brief Implements configPRE_SLEEP_PROCESSING macro.
 */
void idle_onEntrySleep(uint32_t xExpectedIdleTime)
{
  (void)xExpectedIdleTime;
  mcp2551_StandbyMode();
}

/**
  @brief Implements configPOST_SLEEP_PROCESSING macro.
 */
void idle_onExitSleep(uint32_t xExpectedIdleTime)
{
  (void)xExpectedIdleTime;
  mcp2551_HighSpeedMode();
}
