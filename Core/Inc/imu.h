#ifndef IMU_H
#define IMU_H

#include <stdarg.h>
#include <stdint.h>
#include "main.h"

#define IMU_REG_WHO_AM_I 0x0F

typedef enum
{
	BURSTREAD_OK,
	BURSTREAD_INPUT_ERROR,
	BURSTREAD_HAL_ISSUE
} BURSTREAD_StatusTypeDef;

HAL_StatusTypeDef imu_read_reg(uint8_t reg, uint8_t* val);
HAL_StatusTypeDef imu_write_reg(uint8_t reg, uint8_t val);

BURSTREAD_StatusTypeDef imu_burst_read_regs(uint8_t startReg, uint8_t* buf, uint16_t len);

#endif
