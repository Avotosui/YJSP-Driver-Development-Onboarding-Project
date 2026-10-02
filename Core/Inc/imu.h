#ifndef IMU_H
#define IMU_H

#include <stdint.h>
#include "main.h"

#define IMU_REG_WHO_AM_I 0x0F

HAL_StatusTypeDef imu_read_reg(uint8_t reg, uint8_t* val);
HAL_StatusTypeDef imu_write_reg(uint8_t reg, uint8_t val);

#endif
