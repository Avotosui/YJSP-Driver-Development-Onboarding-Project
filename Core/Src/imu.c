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
