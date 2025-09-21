#ifndef Robot_Gibanje_h
#define Robot_Gibanje_h

#include <Arduino.h>

#include "VL53L0XsAnalog.h"   // MRMS VL53L0x LIDAR library
#include <Wire.h>             // Adafruit BNO055 library
#include <Adafruit_Sensor.h>  // Adafruit BNO055 library
#include <Adafruit_BNO055.h>  // Adafruit BNO055 library
#include <utility/imumaths.h> // Adafruit BNO055 library
#include <PID_v1.h>           // PID_v1 by Brett Beauregard library

#define SPEED_LEFT_MOTOR_PIN      37    // 1. motor, pin for motor speed
#define DIRECTION_LEFT_MOTOR_PIN  38    // 1. motor, pin for motor direction
#define SPEED_RIGHT_MOTOR_PIN     35    // 2. motor, pin for motor speed
#define DIRECTION_RIGHT_MOTOR_PIN 36    // 2. motor, pin for motor direction

#define ELECTROMAGNET_PIN1    5     //
#define ELECTROMAGNET_PIN2    3     //

#define FORWARD1_AN_PIN       33    // Forward Left LIDAR - AN pin
#define FORWARD2_AN_PIN       34    // Forward Midium LIDAR - AN pin
#define FORWARD3_AN_PIN       14    // Forward Right LIDAR - AN pin
#define LEFT2_AN_PIN          15    // Left Front LIDAR - AN pin
#define LEFT1_AN_PIN          16    // Left Back LIDAR - AN pin
#define RIGHT2_AN_PIN         17    // Right Front LIDAR - AN pin
#define RIGHT1_AN_PIN         20    // Right Back LIDAR - AN pin
#define BACK1_AN_PIN          21    // Back Left LIDAR - AN pin
#define BACK2_AN_PIN          22    // Back Medium LIDAR - AN pin
#define BACK3_AN_PIN          23    // Back Right LIDAR - AN pin

#define THERMAL_OUT_PIN       32    // Thermal sensor - OUT pin


class ROBOT_GIBANJE {
    public:
    ROBOT_GIBANJE();
    ~ROBOT_GIBANJE();

    int Distance_Array[MAX_VL53L0XS_ANALOG];

    void SetupZaSveKomponente();
    void SetMotorSpeedAndDirection(uint8_t SPEED_PIN, uint8_t DIRECTION_PIN, int motor_speed);
    void Go_Forward(int motor_speed = 60);
    void Go_Back(int motor_speed = -60);
    void Go_Left(int motor_speed = 60);
    void Go_Right(int motor_speed = 60);
    void Stop_Robot();
    uint16_t Read_Forward_Left_Distance();
    uint16_t Read_Forward_Medium_Distance();
    uint16_t Read_Forward_Right_Distance();
    uint16_t Read_Left_Back_Distance();
    uint16_t Read_Left_Front_Distance();
    uint16_t Read_Right_Back_Distance();
    uint16_t Read_Right_Front_Distance();
    uint16_t Read_Back_Left_Distance();
    uint16_t Read_Back_Medium_Distance();
    uint16_t Read_Back_Right_Distance();
    uint16_t Test_All_Distance_Sensors_One_By_One(int sensor_number=0);
    void Read_All_Distances();
    void Go_Forward_30cm(int motor_speed = 50);
    void Go_Back_30cm(int motor_speed = -60);
    void Go_Right_90degrees(int motor_speed = 30);
    void Go_Left_90degrees(int motor_speed = 30);
    void Go_Left_180degrees(int motor_speed = 30); // This function is not deklared


    uint16_t Read_Temperature();

    float Read_Heading();

    bool Is_Wall_Left();    //OR logic operator used
    bool Is_Wall_Right();   //OR logic operator used
    bool Is_Wall_Forward(); //OR logic operator used
    bool Is_Wall_Back();    //OR logic operator used

    bool Moveing_Is_Wall_Opend_Left();    //AND logic operator used
    bool Moveing_Is_Wall_Opend_Right();   //AND logic operator used
    bool Moveing_Is_Wall_Opend_Forward(); //AND logic operator used
    bool Moveing_Is_Wall_Opend_Back();    //AND logic operator used

    bool Moveing_Is_Wall_Left();    //AND logic operator used, closer distance used, center robot
    bool Moveing_Is_Wall_Right();   //AND logic operator used, closer distance used, center robot
    bool Moveing_Is_Wall_Forward(); //AND logic operator used, closer distance used, center robot
    bool Moveing_Is_Wall_Back();    //AND logic operator used, closer distance used, center robot

    void Push_Box();

    void Find_and_Align_Left_Wall();
    void Find_and_Rotate_To_Opend_Wall();
    void Center_Robot();
    void Automomus_Maze_Path_Finding();



};

#endif
