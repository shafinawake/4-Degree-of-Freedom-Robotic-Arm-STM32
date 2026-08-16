#include "pca9685.h"

HAL_StatusTypeDef PCA9685_Init(I2C_HandleTypeDef *hi2c) {
    uint8_t mode1_data;
    HAL_StatusTypeDef status;

    // 1. Read current MODE1 register
    status = HAL_I2C_Mem_Read(hi2c, PCA9685_I2C_ADDR, PCA9685_MODE1, 1, &mode1_data, 1, HAL_MAX_DELAY);
    if (status != HAL_OK) return status;

    // 2. Put PCA9685 to sleep to set PRESCALE register
    uint8_t sleep_mode = (mode1_data & 0x7F) | 0x10; // Set SLEEP bit (bit 4)
    HAL_I2C_Mem_Write(hi2c, PCA9685_I2C_ADDR, PCA9685_MODE1, 1, &sleep_mode, 1, HAL_MAX_DELAY);

    // 3. Write PRESCALE value for 50Hz (121 / 0x79)
    uint8_t prescale_val = 121;
    HAL_I2C_Mem_Write(hi2c, PCA9685_I2C_ADDR, PCA9685_PRESCALE, 1, &prescale_val, 1, HAL_MAX_DELAY);

    // 4. Wake up device and enable Auto-Increment (bit 5 = 0x20)
    uint8_t wake_mode = (mode1_data & ~0x10) | 0x20;
    HAL_I2C_Mem_Write(hi2c, PCA9685_I2C_ADDR, PCA9685_MODE1, 1, &wake_mode, 1, HAL_MAX_DELAY);

    // 5. Wait for oscillator to stabilize
    HAL_Delay(5);

    return HAL_OK;
}

HAL_StatusTypeDef PCA9685_SetPWM(I2C_HandleTypeDef *hi2c, uint8_t channel, uint16_t on, uint16_t off) {
    if (channel > 15) return HAL_ERROR;

    uint8_t buf[4];
    buf[0] = on & 0xFF;
    buf[1] = (on >> 8) & 0xFF;
    buf[2] = off & 0xFF;
    buf[3] = (off >> 8) & 0xFF;

    uint8_t reg_addr = PCA9685_LED0_ON_L + (4 * channel);
    return HAL_I2C_Mem_Write(hi2c, PCA9685_I2C_ADDR, reg_addr, 1, buf, 4, HAL_MAX_DELAY);
}

HAL_StatusTypeDef PCA9685_SetServoAngle(I2C_HandleTypeDef *hi2c, uint8_t channel, float angle) {
    if (angle < 0.0f) angle = 0.0f;
    if (angle > 180.0f) angle = 180.0f;

    uint16_t off_ticks = (uint16_t)(SERVOMIN_TICKS + ((angle / 180.0f) * (SERVOMAX_TICKS - SERVOMIN_TICKS)));
    return PCA9685_SetPWM(hi2c, channel, 0, off_ticks);
}