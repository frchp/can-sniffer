#include "bsp.h"

#include "can.h"
#include "clock.h"
#include "gpio.h"
#include "uart.h"
#include "watchdog.h"
#include "stm32l552xx.h"
#include "FreeRTOSConfig.h"

#define NVIC_PRIORITYGROUP_0         ((uint32_t)0x00000007) /*!< 0 bit  for pre-emption priority,
                                                                 3 bits for subpriority */
#define NVIC_PRIORITYGROUP_1         ((uint32_t)0x00000006) /*!< 1 bit  for pre-emption priority,
                                                                 2 bits for subpriority */
#define NVIC_PRIORITYGROUP_2         ((uint32_t)0x00000005) /*!< 2 bits for pre-emption priority,
                                                                 1 bits for subpriority */
#define NVIC_PRIORITYGROUP_3         ((uint32_t)0x00000004) /*!< 3 bits for pre-emption priority,
                                                                 0 bit  for subpriority */

static void HardFault_Handler_C(uint32_t *hardfault_args);

/**
  @brief Setup the BSP.
 */
void bsp_init (void)
{
  NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_3);

  clock_init();

  // Read access latency needs to be programmed according to CPU clock
  FLASH->ACR &= ~FLASH_ACR_LATENCY;
  FLASH->ACR |= FLASH_ACR_LATENCY_5WS;

  ICACHE->CR |= ICACHE_CR_EN;

  PWR->CR1 |= PWR_CR1_DBP;

  gpio_init();
  can_init();
  uart_init();
}

void SystemInit (void)
{
#if defined(USER_VECT_TAB_ADDRESS)
  SCB->VTOR = (uint32_t)0x08000000 | VECT_TAB_OFFSET;
#endif

#if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
  SCB->CPACR |= ((3UL << 20U)|(3UL << 22U));  /* set CP10 and CP11 Full Access */
#endif
}

void HardFault_Handler(void)
{
  __asm("TST lr, #4");       // Test EXC_RETURN bit
  __asm("ITE EQ");
  __asm("MRSEQ r0, MSP");    // Get stack pointer for main stack
  __asm("MRSNE r0, PSP");    // Get stack pointer for process stack
  __asm("B HardFault_Handler_C");
}

/* Remove warnings for diagnostic function */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
static void HardFault_Handler_C(uint32_t *hardfault_args)
{
  volatile uint32_t r0;
  volatile uint32_t r1;
  volatile uint32_t r2;
  volatile uint32_t r3;
  volatile uint32_t r12;
  volatile uint32_t lr; /* Link register. */
  volatile uint32_t pc; /* Program counter. */
  volatile uint32_t psr;/* Program status register. */
  volatile uint32_t imprecise;

  r0 = hardfault_args[ 0 ];
  r1 = hardfault_args[ 1 ];
  r2 = hardfault_args[ 2 ];
  r3 = hardfault_args[ 3 ];

  r12 = hardfault_args[ 4 ];
  lr = hardfault_args[ 5 ];
  pc = hardfault_args[ 6 ];
  psr = hardfault_args[ 7 ];

  imprecise = SCB->CFSR & SCB_CFSR_IMPRECISERR_Pos;

  Error_Handler(true, ERR_HARD, ERR_TYPE_FAULT);
}
#pragma GCC diagnostic pop

void BusFault_Handler(void)
{
  Error_Handler(true, ERR_BUS, ERR_TYPE_FAULT);
}

void MemManage_Handler(void)
{
  Error_Handler(true, ERR_MEM, ERR_TYPE_FAULT);
}
