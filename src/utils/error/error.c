#include "error.h"

typedef struct
{
  bool b_isCritical;
  Error_Component_t e_component;
  Error_Type_t e_type;
} Error_t;


static Error_t gbl_sLastRecordedError __attribute__(( section(".noinit") ));

/**
 * @brief Handle incoming error
 */
void Error_Handler(bool b_isCritical, Error_Component_t e_component, Error_Type_t e_type)
{
  gbl_sLastRecordedError.b_isCritical = b_isCritical;
  gbl_sLastRecordedError.e_component = e_component;
  gbl_sLastRecordedError.e_type = e_type;

  __asm("bkpt");

  if(b_isCritical)
  {
    // Wait until watchdog reset
    while(1);
  }
  else
  {
    // Save error and let program live
    return;
  }
}