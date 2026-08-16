#ifndef PCA9685_H
#define PCA9685_H

#include "stm32f4xx_hal.h"

#define PCA9685_I2C_ADDR      (0x40 << 1) // Default 7-bit 0x40 shifted for HAL

// Registers
#define PCA9685_MODE1         0x00
#define PCA9685_PRESCALE      0xFE
#define PCA9685_LED0_ON_L     0x06

// Servo Calibration Values (Fine-tune if servos buzz at endpoints)
#define SERVOMIN_TICKS        102  // ~0.5ms (0 deg)
#define SERVOMAX_TICKS        512  // ~2.5ms (180 deg)

// Functions
HAL_StatusTypeDef PCA9685_Init(I2C_HandleTypeDef *hi2c);
HAL_StatusTypeDef PCA9685_SetPWM(I2C_HandleTypeDef *hi2c, uint8_t channel, uint16_t on, uint16_t off);
HAL_StatusTypeDef PCA9685_SetServoAngle(I2C_HandleTypeDef *hi2c, uint8_t channel, float angle);

#endif