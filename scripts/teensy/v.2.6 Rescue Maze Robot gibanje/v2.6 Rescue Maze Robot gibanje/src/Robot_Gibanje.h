#ifndef Robot_Gibanje_h
#define Robot_Gibanje_h

#include <Arduino.h>

#include "VL53L0XsAnalog.h"   // MRMS VL53L0x LIDAR library
#include <Wire.h>             // Adafruit BNO055 library
#include <Adafruit_Sensor.h>  // Adafruit BNO055 library
#include <Adafruit_BNO055.h>  // Adafruit BNO055 library
#include <utility/imumaths.h> // Adafruit BNO055 library
#include <PID_v1.h>           // PID_v1 by Brett Beauregard library

#define SPEED_MOTOR_1_PIN     38    // 1. motor, pin for motor speed
#define DIRECTION_MOTOR_1_PIN 37    // 1. motor, pin for motor direction
#define SPEED_MOTOR_2_PIN     35    // 2. motor, pin for motor speed
#define DIRECTION_MOTOR_2_PIN 36    // 2. motor, pin for motor direction

#define ELECTROMAGNET_PIN1    5     //
#define ELECTROMAGNET_PIN2    3     //

#define FORWARD1_AN_PIN       14    // Forward1 LIDAR - AN pin
#define FORWARD2_AN_PIN       15    // Forward2 LIDAR - AN pin
#define FORWARD3_AN_PIN       16    // Forward3 LIDAR - AN pin
#define LEFT1_AN_PIN          17    // Left1 LIDAR - AN pin
#define LEFT2_AN_PIN          18    // Left2 LIDAR - AN pin
#define RIGHT1_AN_PIN         19    // Right1 LIDAR - AN pin
#define RIGHT2_AN_PIN         20    // Right2 LIDAR - AN pin
#define BACK1_AN_PIN          21    // Back1 LIDAR - AN pin
#define BACK2_AN_PIN          22    // Back2 LIDAR - AN pin
#define BACK3_AN_PIN          23    // Back3 LIDAR - AN pin

#define THERMAL_OUT_PIN       32    // Thermal sensor - OUT pin


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
    uint16_t Read_Forward1_Distance();
    uint16_t Read_Forward2_Distance();
    uint16_t Read_Forward3_Distance();
    uint16_t Read_Right1_Distance();
    uint16_t Read_Right2_Distance();
    uint16_t Read_Left1_Distance();
    uint16_t Read_Left2_Distance();
    uint16_t Read_Back1_Distance();
    uint16_t Read_Back2_Distance();
    uint16_t Read_Back3_Distance();
    void Read_All_Distances();
    void Go_Forward_30cm(int speed_and_direction = 50);
    void Go_Back_30cm(int speed_and_direction = -60);
    void Go_Right_90degrees(int speed_and_direction = 30);
    void Go_Left_90degrees(int speed_and_direction = 30);

    uint16_t Read_Temperature();

    float Read_Heading();

    bool Is_Wall_Left();
    bool Is_Wall_Right();
    bool Is_Wall_Forward();
    bool Is_Wall_Back();

    void Push_Box();

};

#endif
