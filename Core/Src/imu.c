#include "imu.h"

extern SPI_HandleTypeDef hspi1;

HAL_StatusTypeDef imu_read_reg(uint8_t reg, uint8_t* val) {
	uint8_t tx[2] = { reg | 0x80, 0x00 };
	uint8_t rx[2] = { 0 };
	HAL_GPIO_WritePin(IMU_CS_GPIO_Port, IMU_CS_Pin, GPIO_PIN_RESET);
	HAL_StatusTypeDef status = HAL_SPI_TransmitReceive(&hspi1, tx, rx, 2, 100);
	HAL_GPIO_WritePin(IMU_CS_GPIO_Port, IMU_CS_Pin, GPIO_PIN_SET);

	if(status == HAL_OK) {
		*val = rx[1];
	}
	return status;
}

HAL_StatusTypeDef imu_write_reg(uint8_t reg, uint8_t val) {
	uint8_t tx[2] = { reg & 0x7F, val };
	HAL_GPIO_WritePin(IMU_CS_GPIO_Port, IMU_CS_Pin, GPIO_PIN_RESET);
	HAL_StatusTypeDef status = HAL_SPI_Transmit(&hspi1, tx, 2, 100);
	HAL_GPIO_WritePin(IMU_CS_GPIO_Port, IMU_CS_Pin, GPIO_PIN_SET);
	return status;
}

HAL_StatusTypeDef imu_burst_read_regs(uint8_t startReg, uint8_t* buf, uint16_t len) {
	if(buf == NULL || len == 0) return HAL_ERROR;
	uint8_t addr = startReg | 0x80;
	HAL_StatusTypeDef ret = HAL_OK;
	HAL_GPIO_WritePin(IMU_CS_GPIO_Port, IMU_CS_Pin, GPIO_PIN_RESET);
	if(HAL_SPI_Transmit(&hspi1, &addr, 1, 100) != HAL_OK || HAL_SPI_Receive(&hspi1, buf, len, 100) != HAL_OK) {
		ret = HAL_ERROR;
	}
	HAL_GPIO_WritePin(IMU_CS_GPIO_Port, IMU_CS_Pin, GPIO_PIN_SET);
	return ret;
}

HAL_StatusTypeDef imu_configure_accelerometer(IMU_LA_ODR_Setting odr, IMU_LA_FS_Setting fs, IMU_LA_LPF2_Setting lpf2) {
	uint8_t val = (uint8_t) (odr | fs | lpf2);
	return imu_write_reg(IMU_REG_CTRL1_XL, val);
}
