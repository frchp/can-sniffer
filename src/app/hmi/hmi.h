#ifndef _HMI_H_
#define _HMI_H_

/**
  @brief Update human machine interface when processing starts.
 */
void hmi_startProcessing(void);

/**
  @brief Update human machine interface when processing stops.
 */
void hmi_stopProcessing(void);

/**
  @brief Update human machine interface as program is alive.
 */
void hmi_isAlive(void);


#endif // _HMI_H_