#ifndef _IDLE_TASK_H_
#define _IDLE_TASK_H_

/**
 * LPM_MODE_SLEEP     CPU clock OFF, WFI
 * LPM_MODE_LP_SLEEP  CPU clock OFF, Set LPR bit - WFI - Return from ISR
 * LPM_MODE_STOP      All clocks OFF except LSI and LSE, Reg + WFI + Int, wake up pin - RTC - ext reset - wdog reset
 * LPM_MODE_STANDBY   All clocks OFF except LSI and LSE, Reg + WFI + Int, wake up pin - RTC - ext reset - wdog reset
 * LPM_MODE_SHUTDOWN  All clocks OFF except LSE, Reg + WFI + Int, wake up pin - RTC - ext reset - wdog reset
 */

/**
 * FreeRTOS idle :
 * 1. Use idle hook : own LPM implementation, check LPM bitfield to enable entry in LPM
 * enter/exit LPM functions, call for WFI/WFE, load timer to sleep, disable systick, adjust tick count on exit
 * 2. Use FreeRTOS tickless idle : configUSE_TICKLESS_IDLE = 1 : nothing to do
 * 3. Use User tickless idle : configUSE_TICKLESS_IDLE > 1 : similar to idle hook except idle hook can wake up on next tick
 */

#endif // _IDLE_TASK_H_
