#ifndef _I2C_H_
#define _I2C_H_

#include <stdint.h>

#define NO_ERROR  (0u)
#define ERROR     (1u)

void i2c_Init(void);

int i2c_Write(uint8_t addr, uint8_t reg, uint8_t data);

int i2c_Read(uint8_t addr, uint8_t reg, uint8_t *data);

int i2c_WriteBurst(uint8_t addr, uint8_t reg, uint8_t *data, uint8_t len);

int i2c_ReadBurst(uint8_t addr, uint8_t reg, uint8_t *data, uint8_t len);

#endif // _I2C_H_