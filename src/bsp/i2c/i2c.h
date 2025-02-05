#ifndef _I2C_H_
#define _I2C_H_

#include <stdint.h>

#define NO_ERROR  (0u)
#define ERROR     (1u)

void I2C1_Init(void);

int I2C1_Write(uint8_t addr, uint8_t reg, uint8_t data);

int I2C1_Read(uint8_t addr, uint8_t reg, uint8_t *data);

int I2C1_WriteBurst(uint8_t addr, uint8_t reg, uint8_t *data, uint8_t len);

int I2C1_ReadBurst(uint8_t addr, uint8_t reg, uint8_t *data, uint8_t len);

#endif // _I2C_H_