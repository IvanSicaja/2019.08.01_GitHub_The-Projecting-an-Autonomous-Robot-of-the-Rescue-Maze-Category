#ifndef Robot_Gibanje_h
#define Robot_Gibanje_h

#include <Arduino.h>

#include "VL53L0XsAnalog.h"   // MRMS VL53L0x LIDAR library
#include <Wire.h>             // Adafruit BNO055 library
#include <Adafruit_Sensor.h>  // Adafruit BNO055 library
#include <Adafruit_BNO055.h>  // Adafruit BNO055 library
#include <utility/imumaths.h> // Adafruit BNO055 library

#define SPEED_MOTOR_1_PIN     35    // 1. motor, pin for motor speed
#define DIRECTION_MOTOR_1_PIN 36    // 1. motor, pin for motor direction
#define SPEED_MOTOR_2_PIN     38    // 2. motor, pin for motor speed
#define DIRECTION_MOTOR_2_PIN 37    // 2. motor, pin for motor direction

#define LIDAR_AN_PIN          14    // LIDAR - AN pin

#define THERMAL_OUT_PIN       50    // Thermal sensor - OUT pin


class ROBOT_GIBANJE {
public:
        ROBOT_GIBANJE();
        ~ROBOT_GIBANJE();
        void SetupZaSveKomponente();
        void SetMotorSpeedAndDirection(uint8_t SPEED_PIN, uint8_t DIRECTION_PIN, int speed_and_direction);
        void Go_Forward(int speed_and_direction = 6);
        void Go_Back(int speed_and_direction = -6);
        void Go_Left(int speed_and_direction = 6);
        void Go_Right(int speed_and_direction = 6);
        void Stop_Robot();
        void Go_Forward_30cm(int speed_and_direction = 6);
        void Go_Right_90degrees(int speed_and_direction = 2);
        void Go_Left_90degrees(int speed_and_direction = 2);

        uint16_t Read_Temperature();

        float Read_Heading();
};

#endif
