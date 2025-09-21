#ifndef Robot_Gibanje_h
#define Robot_Gibanje_h

#include <Arduino.h>

#include "VL53L0XsAnalog.h"   // MRMS VL53L0x LIDAR library
#include <Wire.h>             // Adafruit BNO055 library
#include <Adafruit_Sensor.h>  // Adafruit BNO055 library
#include <Adafruit_BNO055.h>  // Adafruit BNO055 library
#include <utility/imumaths.h> // Adafruit BNO055 library
#include <PID_v1.h>           // PID_v1 by Brett Beauregard library

#define SPEED_BACK_LEFT_MOTOR_PIN        2    // 1. motor, pin for motor speed
#define DIRECTION_BACK_LEFT_MOTOR_PIN    3    // 1. motor, pin for motor direction
#define SPEED_BACK_RIGHT_MOTOR_PIN       4    // 2. motor, pin for motor speed
#define DIRECTION_BACK_RIGHT_MOTOR_PIN   5    // 2. motor, pin for motor direction
#define SPEED_FRONT_LEFT_MOTOR_PIN       6    // 3. motor, pin for motor speed
#define DIRECTION_FRONT_LEFT_MOTOR_PIN   7    // 3. motor, pin for motor direction
#define SPEED_FRONT_RIGHT_MOTOR_PIN      8    // 4. motor, pin for motor speed
#define DIRECTION_FRONT_RIGHT_MOTOR_PIN  9    // 4. motor, pin for motor direction

#define ENCODER_LEFT_A_OUT    54
#define ENCODER_LEFT_B_OUT    55
#define ENCODER_RIGHT_A_OUT   56
#define ENCODER_RIGHT_B_OUT   57


#define ELECTROMAGNET_PIN1    29     //
#define ELECTROMAGNET_PIN2    30     //

#define FORWARD1_AN_PIN       33    // Forward Left LIDAR - AN pin
#define FORWARD3_AN_PIN       34    // Forward Right LIDAR - AN pin
#define LEFT2_AN_PIN          35    // Left Front LIDAR - AN pin
#define LEFT1_AN_PIN          36    // Left Back LIDAR - AN pin
#define RIGHT2_AN_PIN         37    // Right Front LIDAR - AN pin
#define RIGHT1_AN_PIN         38    // Right Back LIDAR - AN pin
#define BACK1_AN_PIN          39    // Back Left LIDAR - AN pin

#define FORWARD2_AN_PIN       14    // Forward Midium LIDAR - AN pin
#define BACK3_AN_PIN          15    // Back Right LIDAR - AN pin
#define BACK2_AN_PIN          16    // Back Middle LIDAR - AN pin

#define THERMAL_OUT_PIN       32    // Thermal sensor - OUT pin

// Color sensor pins
#define S0 46
#define S1 45
#define S2 44
#define S3 43
#define sensorOut 42

 


class ROBOT_GIBANJE {
    public:
    ROBOT_GIBANJE();
    ~ROBOT_GIBANJE();

    int Distance_Array[MAX_VL53L0XS_ANALOG];

    int Front_Stop_Distance_Check=120;

    void SetupZaSveKomponente();
    void SetMotorSpeedAndDirection(uint8_t SPEED_PIN, uint8_t DIRECTION_PIN, int motor_speed);
    void Go_Forward(int left_motor_speed=20, int right_motor_speed=20);
    void Go_Back(int motor_speed = -30);
    void Go_Left(int motor_speed = 30);
    void Go_Right(int motor_speed = 30);
    void Stop_Robot();
    uint16_t Read_Forward_Left_Distance();
    uint16_t Read_Forward_Middle_Distance();
    uint16_t Read_Forward_Right_Distance();
    uint16_t Read_Left_Back_Distance();
    uint16_t Read_Left_Front_Distance();
    uint16_t Read_Right_Back_Distance();
    uint16_t Read_Right_Front_Distance();
    uint16_t Read_Back_Left_Distance();
    uint16_t Read_Back_Middle_Distance();
    uint16_t Read_Back_Right_Distance();
    void Test_All_Distance_Sensors_One_By_One(int sensor_number=0);
    void Read_All_Distances();
    void Go_Forward_30cm(int motor_speed = 30);
    void Go_Back_30cm(int motor_speed = -30);
    void Go_Right_90degrees(int motor_speed = 30);
    void Go_Left_90degrees(int motor_speed = 30);
    void Go_180degrees(int motor_speed=30 ); // This function is not deklared
    

    void Rotate_Right_With_Specific_Angle(int angle, int delayTime=0, int motor_speed=30); //angle ust be  values between 0 and 90 degrees
    void Rotate_Left_With_Specific_Angle(int angle, int delayTime=0, int motor_speed=30);  //angle ust be  values between 0 and 90 degrees

    int Align_To_Left_Wall(int Alowed_Error=1, int delayTime=0);
    int Front_Stop_Distance(float Maze_Plate_Lenght=325,float Snesor_Distance_From_Robot_Center_Point=67.167);
    void Follow_Gyrosope_With_PID_Controller(int Orientation_Tolerance = 1,int delayTime=0,int LeftandRightSpeed=20);

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

    // Color sensor functions
    void Search_for_Black_or_Grey_tiles();
    int getRedPW();
    int getGreenPW();
    int getBluePW();

    void Go_Forward_PID_Corrected(int Orientation_Tolerance = 1, int delayTime = 0);
    void Read_Right_Encoder ( int right_motor_speed=20);
    void Read_Left_Encoder ( int left_motor_speed=20);
 
    



};

#endif
