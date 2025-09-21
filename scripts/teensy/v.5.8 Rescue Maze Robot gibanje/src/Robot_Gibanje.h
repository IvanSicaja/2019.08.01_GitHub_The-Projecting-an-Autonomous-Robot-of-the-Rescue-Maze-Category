#ifndef Robot_Gibanje_h
#define Robot_Gibanje_h

//############################################################## Includeing libraries ##############################################################

#include <Arduino.h>

#include <Wire.h>             //
#include <Adafruit_Sensor.h>  //
#include <Adafruit_BNO055.h>  // Library used for read gyroscope data from Adafruit BNO055 
#include <util/atomic.h>      // Library used for createing atomic blocks which is used with read encoders functions
#include <utility/imumaths.h> //

//################################################################ Pins definitions ################################################################

#define SPEED_BACK_LEFT_MOTOR_PIN 2       // 1. motor - pin for motor speed
#define DIRECTION_BACK_LEFT_MOTOR_PIN 3   // 1. motor - pin for motor direction
#define SPEED_BACK_RIGHT_MOTOR_PIN 4      // 2. motor - pin for motor speed
#define DIRECTION_BACK_RIGHT_MOTOR_PIN 5  // 2. motor - pin for motor direction
#define SPEED_FRONT_LEFT_MOTOR_PIN 6      // 3. motor - pin for motor speed
#define DIRECTION_FRONT_LEFT_MOTOR_PIN 7  // 3. motor - pin for motor direction
#define SPEED_FRONT_RIGHT_MOTOR_PIN 8     // 4. motor - pin for motor speed
#define DIRECTION_FRONT_RIGHT_MOTOR_PIN 9 // 4. motor - pin for motor direction

#define ENCODER_LEFT_A_OUT 54  // Left encoder - A output pin
#define ENCODER_LEFT_B_OUT 55  // Left encoder - B output pin
#define ENCODER_RIGHT_A_OUT 56 // Right encoder - A output pin
#define ENCODER_RIGHT_B_OUT 57 // Right encoder - B output pin

#define ELECTROMAGNET_PIN1 29 // Not used - solednoid is controlled by Raspberry Pi
#define ELECTROMAGNET_PIN2 30 // Not used - solednoid is controlled by Raspberry Pi

#define FORWARD1_AN_PIN 33 // Forward Left LIDAR - analog output pin
#define FORWARD2_AN_PIN 34 // Forward Right LIDAR - analog output pin
#define LEFT1_AN_PIN 35    // Left Front LIDAR - analog output pin
#define LEFT2_AN_PIN 36    // Left Back LIDAR - analog output pin
#define RIGHT1_AN_PIN 37   // Right Front LIDAR - analog output pin
#define RIGHT2_AN_PIN 38   // Right Back LIDAR - analog output pin

#define LEFT_THERMAL_CAM_OUT_PIN 23  // Left thermal camera - analog output pin
#define RIGHT_THERMAL_CAM_OUT_PIN 22 // Right thermal camera - analog output pin

#define S0 46        // Color sensor - pin used for color snesor output fequency scalling
#define S1 45        // Color sensor - pin used for color snesor output fequency scalling
#define S2 44        // Color sensor - pin used for choose reading color from color sensor
#define S3 43        // Color sensor - pin used for choose reading color from color sensor
#define sensorOut 42 // Color sensor - output

//###################################################### Class and class functions definitions ##########################################################

class ROBOT_GIBANJE
{

    //##################################################### Define class constructor and destructor #####################################################

public:
    ROBOT_GIBANJE();  // Class construktor
    ~ROBOT_GIBANJE(); // Class destructor

    //############################################################## Read sensor functions ##############################################################

    // Read distance sensors functions
    uint16_t Read_Forward_Left_Distance();
    uint16_t Read_Forward_Right_Distance();
    uint16_t Read_Left_Front_Distance();
    uint16_t Read_Left_Back_Distance();
    uint16_t Read_Right_Front_Distance();
    uint16_t Read_Right_Back_Distance();
    void Read_All_Distances(int delayInMicroseconds = 1000); //Successed test
    uint16_t Read_Forward_Left_Distance_Millimetters();
    uint16_t Read_Forward_Right_Distance_Millimetters();
    uint16_t Read_Left_Front_Distance_Millimetters();
    uint16_t Read_Left_Back_Distance_Millimetters();
    uint16_t Read_Right_Front_Distance_Millimetters();
    uint16_t Read_Right_Back_Distance_Millimetters();
    void Read_All_Distances_Millimetters(int delayInMicroseconds = 1000); //Successed test
    //Read gyroscope functions
    float Read_Gyroscope_X_Axis_Orientation(); // Read x-axis robot orientation
    float Read_Gyroscope_Z_Axis_Orientation(); // Read z-axis robot orientation
    //Read thermal camera functions
    void Read_Temperature_Left_Sensor();  // Read left thermal camera value
    void Read_Temperature_Right_Sensor(); // Not defined
    //Read encoder functions
    int Read_Right_Encoder(int right_motor_speed = 20);
    int Read_Left_Encoder(int left_motor_speed = 20);
    // Read color sensor functions
    int getRedPW();
    int getGreenPW();
    int getBluePW();
    int Search_for_Black_or_Grey_tiles(); // Search function for black and grey tiles

    //########################################################## All components setup function ##########################################################

    void Setup_For_All_Components();

    //########################################################## Basic robot moveing functions ##########################################################

    void SetMotorSpeedAndDirection(uint8_t SPEED_PIN, uint8_t DIRECTION_PIN, int motor_speed);
    void Go_Forward(int left_motor_speed = 20, int right_motor_speed = 20);
    void Go_Forward_30cm(int motor_speed = 30); // Not used, undefined - will use encoders to measure 30 cm distance
    void Go_Back(int motor_speed = -30);
    void Go_Back_30cm(int motor_speed = -30); // Not used, undefined - will use encoders to measure 30 cm distance
    void Go_Left(int motor_speed = 30);
    void Go_Right(int motor_speed = 30);
    void Stop_Robot();
    void Rotate_Right_With_Specific_Angle(int angle, int delayTime = 0, int motor_speed = 30); // Angle must be values between 0 and 89 degrees
    void Rotate_Left_With_Specific_Angle(int angle, int delayTime = 0, int motor_speed = 30);  // Angle must be values between 0 and 89 degrees
    void Rotate_Robot_For_180_degrees(int motor_speed = 30);                                   // Rotate robot for 180 degrees

    //############################################################# Wall detection functions ########################################################################

    bool Stopped_Is_Wall_Left_OR_Logic();     //OR logic operator used
    bool Stopped_Is_Wall_Right_OR_Logic();    //OR logic operator used
    bool Stopped_Is_Wall_Forward_OR_Logic();  //OR logic operator used
    bool Stopped_Is_Wall_Left_AND_Logic();    //AND logic operator used
    bool Stopped_Is_Wall_Right_AND_Logic();   //AND logic operator used
    bool Stopped_Is_Wall_Forward_AND_Logic(); //AND logic operator used

    bool Moveing_Is_Wall_Forward_OR_Logic();  //OR logic operator used
    bool Moveing_Is_Wall_Forward_AND_Logic(); //AND logic operator used

    int Align_To_Left_Wall(int Alowed_Error = 1, int delayTime = 0);  //Successed test
    int Align_To_Right_Wall(int Alowed_Error = 1, int delayTime = 0); //Successed test
    int Align_To_Front_Wall(int Alowed_Error = 1, int delayTime = 0); //Successed test

    void Find_and_Rotate_To_Opend_Wall(int opendWallsDIstance = 30, int delayInMicroseconds = 1000); // Works fine - needs more testing

    //############################################################## P-regulator functions #################################################################################################################################################

    void Stay_Away_From_Left_Wall(int wanted_running_function_time=500);                                           // Works fine - need P regulator paremetters calibration
    void Stay_Away_From_Right_Wall(int wanted_running_function_time=500);                                          // Works fine - need P regulator paremetters calibration
    void Keep_Optimal_Distance_With_Left_Wall(int Ideal_Left_Distance = 13);   // Works fine - need P regulator paremetters calibration
    void Keep_Optimal_Distance_With_Right_Wall(int Ideal_Right_Distance = 13); // Works fine - need P regulator paremetters calibration
    int Optimize_speed_with_Z_Orientation(int Z_Orientatio_Tolerance = 13);

    void Go_Forward_And_Follow_Gyroscope_P_Regulator(int Setpoint1, int Orientation_Tolerance = 1, int delayTime = 0);                                    // Follow x-axis orinetation
    void Go_Forward_Follow_Gyroscope_And_Stop_In_Front_Of_Wall_P_Regulator(int Orientation_Tolerance = 1, int delayTime = 0, int LeftandRightSpeed = 20); // Follow x-axis orinetation and stops when the wall is in front of robot

    //############################################################## Functions optimized for autonomus loop ##########################################################################################################################################################################################################################################################

    void Stay_Away_From_Left_Wall_Optimized_For_Autonomus_Loop(int Left_Front_Distance, int Forward_Left_distance, int Forward_Right_distance, boolean founded_black_or_gray_tiles, int left_and_right_motor_speed, int Go_Forward_Delay=100,int wanted_running_function_time=600);                                              // Works fine - need P regulator paremetters calibration
    void Stay_Away_From_Right_Wall_Optimized_For_Autonomus_Loop(int Right_Front_Distance, int Forward_Left_distance, int Forward_Right_distance, boolean founded_black_or_gray_tiles, int left_and_right_motor_speed, int Go_Forward_Delay=100, int wanted_running_function_time=600);                                            // Works fine - need P regulator paremetters calibration
    void Keep_Optimal_Distance_With_Left_Wall_Optimized_For_Autonomus_Loop( int Left_Front_Distance, int Forward_Left_distance, int Forward_Right_distance, boolean founded_black_or_gray_tiles, int left_and_right_motor_speed, int Go_Forward_Delay=100, int Ideal_Left_Distance = 13);   // Works fine - need P regulator paremetters calibration
    void Keep_Optimal_Distance_With_Right_Wall_Optimized_For_Autonomus_Loop(int Right_Front_Distance, int Forward_Left_distance, int Forward_Right_distance, boolean founded_black_or_gray_tiles, int left_and_right_motor_speed, int Go_Forward_Delay=100,int Ideal_Right_Distance = 13);  // Works fine - need P regulator paremetters calibration
    int Optimize_speed_with_Z_Orientation_Optimized_For_Autonomus_Loop(int left_and_right_motor_speed,int Z_Orientation_Tolerance = 13);

    void Listen_Serial_Port_Optimized_For_Autonomus_Loop();

    //############################################################## Rescue Maze robot tasks autonomus functions #####################################################################################################################################################################################################################################################

    void Go_Autonomus_Basic_Version(int Orientation_Tolerance = 1, int delayTime = 0);
    void Go_Autonomus_Adventage_Version(int Orientation_Tolerance = 1, int delayTime = 0);
    void Go_Autonomus_Adventage_Version_Optimized(int Orientation_Tolerance = 1, boolean Avoid_Side_Walls_P_Regulator_Turned_On = true, boolean Keep_Optimal_Distance_With_Side_Walls_P_Regulator_Turned_On = false, boolean Optimize_Speed_With_Z_Axis_Value_P_Regulator_Turned_On = true, int delayTime = 0);

    //############################################################### Not used functions #############################################################################################################################################################################################################################################################################

    void Push_Box();                    // Not used because Raspberry Pi does pushing box
    void Find_and_Align_Left_Wall();    // Not used
    void Center_Robot();                // Not used
    void Automomus_Maze_Path_Finding(); // Not used
};

#endif
