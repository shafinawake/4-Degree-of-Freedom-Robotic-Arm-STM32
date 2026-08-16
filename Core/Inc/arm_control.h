#ifndef ARM_CONTROL_H
#define ARM_CONTROL_H

#include "main.h" // Provides I2C_HandleTypeDef and HAL types

typedef struct {
    uint8_t channel;
    float current_angle;
    float target_angle;
    float speed;
} Joint_t;

typedef struct {
    Joint_t joints[4];
} Arm_t;

 void Arm_Update(I2C_HandleTypeDef *hi2c, Arm_t *arm, float dt_seconds);

#endif /* ARM_CONTROL_H */