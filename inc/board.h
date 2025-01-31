#ifndef _BOARD_H_
#define _BOARD_H_

#define USE_ST_NUCLEO

#define SYSTEM_CLOCK_FREQ_HZ  (110000000ul)

#ifdef USE_ST_NUCLEO
  // We use the Nucleo, clock is supplied by MCO from STLink @ 8MHz
#else
  // We use the STM32L552 not on the Nucleo, the clock is supplied by HSE @ ?MHz
#endif // USE_ST_NUCLEO

#endif _BOARD_H_