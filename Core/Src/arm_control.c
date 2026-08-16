#include "arm_control.h"
#include "pca9685.h" // Replace with your actual PCA9685 header file name
#include <math.h>   // Required for fabsf()

void Arm_Update(I2C_HandleTypeDef *hi2c, Arm_t *arm, float dt_seconds) {
    for (int i = 0; i < 4; i++) {
        Joint_t *j = &arm->joints[i];
        
        if (j->current_angle != j->target_angle) {
            float diff = j->target_angle - j->current_angle;
            float max_step = j->speed * dt_seconds;

            if (fabsf(diff) <= max_step) {
                j->current_angle = j->target_angle; // Reached target
            } else {
                j->current_angle += (diff > 0 ? max_step : -max_step);
            }

            PCA9685_SetServoAngle(hi2c, j->channel, j->current_angle);
        }
    }
}