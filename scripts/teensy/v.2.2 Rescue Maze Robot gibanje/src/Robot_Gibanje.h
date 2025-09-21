#ifndef Robot_Gibanje_h
#define Robot_Gibanje_h

#include <Arduino.h>

#include "VL53L0XsAnalog.h"   // MRMS VL53L0x LIDAR library
#include <Wire.h>             // Adafruit BNO055 library
#include <Adafruit_Sensor.h>  // Adafruit BNO055 library
#include <Adafruit_BNO055.h>  // Adafruit BNO055 library
#include <utility/imumaths.h> // Adafruit BNO055 library

#define SPEED_MOTOR_1_PIN     38    // 1. motor, pin for motor speed
#define DIRECTION_MOTOR_1_PIN 37    // 1. motor, pin for motor direction
#define SPEED_MOTOR_2_PIN     35    // 2. motor, pin for motor speed
#define DIRECTION_MOTOR_2_PIN 36    // 2. motor, pin for motor direction

#define LIDAR1_AN_PIN         14    // LIDAR - AN pin
#define LIDAR2_AN_PIN         15    // LIDAR - AN pin
#define LIDAR3_AN_PIN         16    // LIDAR - AN pin

#define THERMAL_OUT_PIN       50    // Thermal sensor - OUT pin


class ROBOT_GIBANJE {
public:
ROBOT_GIBANJE();
~ROBOT_GIBANJE();

int Distance_Array[MAX_VL53L0XS_ANALOG];

void SetupZaSveKomponente();
void SetMotorSpeedAndDirection(uint8_t SPEED_PIN, uint8_t DIRECTION_PIN, int speed_and_direction);
void Go_Forward(int speed_and_direction = 60);
void Go_Back(int speed_and_direction = -60);
void Go_Left(int speed_and_direction = 60);
void Go_Right(int speed_and_direction = 60);
void Stop_Robot();
void Go_Forward_30cm(int speed_and_direction = 60);
void Go_Back_30cm(int speed_and_direction = -60);
void Read_All_Distances();
void Go_Right_90degrees(int speed_and_direction = 30);
void Go_Left_90degrees(int speed_and_direction = 30);

uint16_t Read_Temperature();

float Read_Heading();
};

#endif
