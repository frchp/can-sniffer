#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#include "stm32l552xx.h" // Include STM32-specific header
#include "board.h"
#include "idle_task.h"
#include "error.h"
#include <assert.h>

/*-----------------------------------------------------------
 * FreeRTOS Kernel Configuration
 *----------------------------------------------------------*/

/* Cortex-M specific definitions */
#define configUSE_PREEMPTION                  1
#define configCPU_CLOCK_HZ                    (SYSTEM_CLOCK_FREQ_HZ) // CPU Clock Frequency
#define configTICK_RATE_HZ                    (1000u) // 1 ms tick
#define configMAX_PRIORITIES                  5                 // Maximum number of priorities
#define configMINIMAL_STACK_SIZE              ((uint16_t)128)   // Minimal stack size in words
#define configTOTAL_HEAP_SIZE                 0                 // No heap needed for static allocation
#define configMAX_TASK_NAME_LEN               16                // Task name length
#define configUSE_16_BIT_TICKS                0                 // Use 32-bit ticks
#define configIDLE_SHOULD_YIELD               1                 // Idle task yields CPU time

/* Hook function definitions */
#define configUSE_IDLE_HOOK                   0                 // Idle hook
#define configUSE_TICK_HOOK                   0                 // No tick hook
#define configCHECK_FOR_STACK_OVERFLOW        2                 // Enable stack overflow checking
#define configUSE_MALLOC_FAILED_HOOK          0                 // Enable malloc failed hook

/* Software timer definitions */
#define configUSE_TIMERS                      1                 // Enable software timers
#define configTIMER_TASK_PRIORITY             (configMAX_PRIORITIES - 1) // Highest priority for timer task
#define configTIMER_QUEUE_LENGTH              10                // Timer queue length
#define configTIMER_TASK_STACK_DEPTH          (configMINIMAL_STACK_SIZE * 2) // Timer task stack size

/* Memory allocation related definitions */
#define configSUPPORT_DYNAMIC_ALLOCATION      0                 // Enable dynamic memory allocation
#define configSUPPORT_STATIC_ALLOCATION       1                 // Enable static memory allocation

/* Mutex and semaphore definitions */
#define configUSE_MUTEXES                     1                 // Enable mutexes
#define configUSE_RECURSIVE_MUTEXES           1                 // Enable recursive mutexes
#define configUSE_COUNTING_SEMAPHORES         1                 // Enable counting semaphores
#define configQUEUE_REGISTRY_SIZE             10                // Queue registry size for debugging

/* Run time and task stats gathering */
#define configGENERATE_RUN_TIME_STATS         0                 // Disable run time stats
#define configUSE_TRACE_FACILITY              0                 // Enable trace facility
#define configUSE_STATS_FORMATTING_FUNCTIONS  0                 // Enable stats formatting

/* Co-routine definitions (optional) */
#define configUSE_CO_ROUTINES                 0                 // Disable co-routines
#define configMAX_CO_ROUTINE_PRIORITIES       2                 // Max co-routine priorities

/* Interrupt nesting behavior configuration */
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY         7
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY    5
#define configKERNEL_INTERRUPT_PRIORITY       (configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - __NVIC_PRIO_BITS)) // Lowest priority
#define configMAX_SYSCALL_INTERRUPT_PRIORITY  (configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - __NVIC_PRIO_BITS))  // Priority for FreeRTOS API calls

/* Define to trap errors during development */
#define configASSERT(x) if ((x) == 0) { Error_Handler(true, ERR_OS, ERR_TYPE_FAULT); }

/* Idle */
#define configEXPECTED_IDLE_TIME_BEFORE_SLEEP 5
#define configUSE_TICKLESS_IDLE               1                 // 1 to enable, 2 to create specific port
#define configPRE_SLEEP_PROCESSING(xExpectedIdleTime)     idle_onEntrySleep(xExpectedIdleTime)
#define configPOST_SLEEP_PROCESSING(xExpectedIdleTime)    idle_onExitSleep(xExpectedIdleTime)

/*-----------------------------------------------------------
 * Optional functions
 *----------------------------------------------------------*/
#define INCLUDE_vTaskPrioritySet              1
#define INCLUDE_uxTaskPriorityGet             1
#define INCLUDE_vTaskDelete                   1
#define INCLUDE_vTaskSuspend                  1
#define INCLUDE_xResumeFromISR                1
#define INCLUDE_vTaskDelayUntil               1
#define INCLUDE_vTaskDelay                    1
#define INCLUDE_xTaskGetSchedulerState        1
#define INCLUDE_xTaskGetCurrentTaskHandle     1
#define INCLUDE_uxTaskGetStackHighWaterMark   1
#define INCLUDE_xTaskGetIdleTaskHandle        1
#define INCLUDE_eTaskGetState                 1

/*-----------------------------------------------------------
 * FreeRTOS Secure Configuration (Cortex-M33 specific)
 *----------------------------------------------------------*/
#define configENABLE_MPU                  0                 // Enable MPU support
#define configENABLE_FPU                  1                 // Enable FPU support
#define configENABLE_TRUSTZONE            0                 // Enable TrustZone support
#define configRUN_FREERTOS_SECURE_ONLY    0                 // Use FreeRTOS in secure and non-secure modes

#endif /* FREERTOS_CONFIG_H */
