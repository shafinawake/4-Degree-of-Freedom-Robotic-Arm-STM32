This is a project where the robotic arm will perform "pick" & "place" operations. STM32F401RET6 is the MCU that will be used here, along with 16 channel 12 bit PWM.

This is done in CMake, so to run it one needs to set up VS Code. STM32 has good guidelines on how to set up VS Code for STM32 works. 

Also, the components to build the arm are as follows 
1. Arm: https://store.roboticsbd.com/learning-kit/669-6dof-aluminium-mechanical-robotic-arm-clamp-claw-mount-robot-kit.html
2. 6 MG996R servo motors 
    NOTE: They don't provide the metal SEVO HORN, which one needs to buy separately
3. SERVO MOTOR HORN: https://store.roboticsbd.com/robotics-parts/829-metal-servo-horn-robotics-bangladesh.html
4. 16 Channel PWM: https://store.roboticsbd.com/motor-driver/289-16-channel-12-bit-pwm-servo-driver-i2c-interface-pca9685-robotics-bangladesh.html
5. Used 3S LiPo batteries, but it's one's choice 
6. DC-DC step-down converter module: https://store.roboticsbd.com/components/730-dc-dc-boost-module-xl6009-robotics-bangladesh.html

Just download the zip, adjust pins according to ".ioc" file and you are good to go :) 
