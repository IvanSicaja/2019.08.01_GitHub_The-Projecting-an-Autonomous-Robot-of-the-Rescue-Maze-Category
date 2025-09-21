//************************************************************************************************************

// Library definitions
#include <Arduino.h>          // Comment this line if you use Arduino IDE
#include "VL53L0XsAnalog.h"   // MRMS VL53L0x LIDAR library
#include <Wire.h>             // Adafruit BNO055 library
#include <Adafruit_Sensor.h>  // Adafruit BNO055 library
#include <Adafruit_BNO055.h>  // Adafruit BNO055 library
#include <utility/imumaths.h> // Adafruit BNO055 library

//************************************************************************************************************

//************************************************************************************************************

// Object definitions
VL53L0XsAnalog lidar; // LIDAR object
Adafruit_BNO055 gyroscope = Adafruit_BNO055(55); // Gyroscope object

//************************************************************************************************************

//************************************************************************************************************

// Pin definitions
#define SPEED_MOTOR_1_PIN     35    // 1. motor, pin for motor speed
#define DIRECTION_MOTOR_1_PIN 36    // 1. motor, pin for motor direction
#define SPEED_MOTOR_2_PIN     38    // 2. motor, pin for motor speed
#define DIRECTION_MOTOR_2_PIN 37    // 2. motor, pin for motor direction

#define LIDAR_AN_PIN          14    // LIDAR - AN pin

#define THERMAL_OUT_PIN       50    // Thermal sensor - OUT pin

//************************************************************************************************************

//************************************************************************************************************

// Function prototypes
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

//************************************************************************************************************

//************************************************************************************************************

// Function definitions
void SetMotorSpeedAndDirection(uint8_t SPEED_PIN, uint8_t DIRECTION_PIN, int speed_and_direction){

        if((speed_and_direction >= (-10))&&(speed_and_direction <= 10)) { // speed_and_direction needs to be from -10 to 10
                if(speed_and_direction > 0) {                             // when this number is negative motor goes forward, when negative it goes backwards
                        speed_and_direction = map(speed_and_direction,0,10,0,255);
                        digitalWrite(DIRECTION_PIN, LOW);
                        analogWrite(SPEED_PIN, speed_and_direction);
                }
                else if(speed_and_direction < 0) {
                        speed_and_direction = map(speed_and_direction,-10,0,0,255);
                        digitalWrite(DIRECTION_PIN, HIGH);
                        analogWrite(SPEED_PIN, speed_and_direction);
                }
                else {
                        analogWrite(DIRECTION_PIN, 0);
                        analogWrite(SPEED_PIN, 0);
                }
        }

}

void Go_Forward(int speed_and_direction = 6){ // Default speed is maximum when you don't send any value to function

        SetMotorSpeedAndDirection(SPEED_MOTOR_1_PIN, DIRECTION_MOTOR_1_PIN, speed_and_direction);
        SetMotorSpeedAndDirection(SPEED_MOTOR_2_PIN, DIRECTION_MOTOR_2_PIN, speed_and_direction);
        // Serial.println("Go_Forward() function is called.");

}


void Go_Back(int speed_and_direction = -6){ // Default speed is maximum when you don't send any value to function

        SetMotorSpeedAndDirection(SPEED_MOTOR_1_PIN, DIRECTION_MOTOR_1_PIN, speed_and_direction);
        SetMotorSpeedAndDirection(SPEED_MOTOR_2_PIN, DIRECTION_MOTOR_2_PIN, speed_and_direction);
        // Serial.println("Go_Back() function is called.");

}

void Go_Left(int speed_and_direction = 6){ // Default speed is maximum when you don't send any value to function

        SetMotorSpeedAndDirection(SPEED_MOTOR_1_PIN, DIRECTION_MOTOR_1_PIN, -speed_and_direction);
        SetMotorSpeedAndDirection(SPEED_MOTOR_2_PIN, DIRECTION_MOTOR_2_PIN, speed_and_direction);
        // Serial.println("Go_Left() function is called.");

}

void Go_Right(int speed_and_direction = 6){ // Default speed is maximum when you don't send any value to function

        SetMotorSpeedAndDirection(SPEED_MOTOR_1_PIN, DIRECTION_MOTOR_1_PIN, speed_and_direction);
        SetMotorSpeedAndDirection(SPEED_MOTOR_2_PIN, DIRECTION_MOTOR_2_PIN, -speed_and_direction);
        // Serial.println("Go_Right() function is called.");

}

void Stop_Robot(){

        SetMotorSpeedAndDirection(SPEED_MOTOR_1_PIN, DIRECTION_MOTOR_1_PIN, 0);
        SetMotorSpeedAndDirection(SPEED_MOTOR_2_PIN, DIRECTION_MOTOR_2_PIN, 0);
        // Serial.println("Stop_Robot() function is called.");

}

void Go_Forward_30cm(int speed_and_direction = 6){ // Default speed is maximum when you don't send any value to function

        uint16_t first_distance = lidar.distance();
        uint16_t allowed_error = 0; // This number can be changed to achieve correct movement
        while(lidar.distance() > (first_distance - 300 + allowed_error)) {
                Go_Forward(speed_and_direction);
        }
        Stop_Robot();
        // Serial.println("Go_Forward_30cm() function is called.");

}

float Read_Heading(){

        sensors_event_t event;
        gyroscope.getEvent(&event);
        return event.orientation.x;

}

// When going right angle is increasing from 0 to 360
void Go_Right_90degrees(int speed_and_direction = 2){ // Default speed for turning right is 2, when you don't send any value to function

        uint16_t initial_heading = Read_Heading();
        uint8_t allowed_error = 1; // This number can be changed to achieve precise turns
        if(initial_heading < 270) {
                while(Read_Heading() < (initial_heading + 90 - allowed_error)) {
                        Go_Right(speed_and_direction);
                }
        }
        else{
                while((Read_Heading() <= 360) && (Read_Heading() >= 270)) {
                        Go_Right(speed_and_direction);
                }
                while(Read_Heading() < (initial_heading - 270 - allowed_error)) {
                        Go_Right(speed_and_direction);
                }
        }
        Stop_Robot();
        // Serial.println("Go_Right_90degrees() function is called.");

}

// When going left angle is decreasing from 360 to 0
void Go_Left_90degrees(int speed_and_direction = 2){ // Default speed for turning left is 2, when you don't send any value to function

        uint16_t initial_heading = Read_Heading();
        uint8_t allowed_error = 1; // This number can be changed to achieve precise turns
        if(initial_heading > 90) {
                while(Read_Heading() > (initial_heading - 90 + allowed_error)) {
                        Go_Left(speed_and_direction);
                }
        }
        else{
                while((Read_Heading() >= 0) && (Read_Heading() <= 90)) {
                        Go_Left(speed_and_direction);
                }
                while(Read_Heading() > (initial_heading + 270 + allowed_error)) {
                        Go_Left(speed_and_direction);
                }
        }
        Stop_Robot();
        // Serial.println("Go_Left_90degrees() function is called.");

}

uint16_t Read_Temperature(){

        return analogRead(THERMAL_OUT_PIN);

}

//************************************************************************************************************

//************************************************************************************************************

// Setup function
void setup() {

        Serial.begin(115200); // Start communication with a computer connected to Teensy via a USB cable

        lidar.add(LIDAR_AN_PIN); // Analog input Teensy pin 14, connected to LIDAR's AN output

        pinMode(THERMAL_OUT_PIN, INPUT); // Analog input pin 18, connected to thermal sensor OUT output

        pinMode(SPEED_MOTOR_1_PIN, OUTPUT);
        pinMode(DIRECTION_MOTOR_1_PIN, OUTPUT);
        pinMode(SPEED_MOTOR_2_PIN, OUTPUT);
        pinMode(DIRECTION_MOTOR_2_PIN, OUTPUT);

        if(!gyroscope.begin())
        {
                /* There was a problem detecting the BNO055 ... check your connections */
                Serial.print(F("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!"));
                while(1);
        }
        delay(1000);
        gyroscope.setExtCrystalUse(true);

}

//************************************************************************************************************

//************************************************************************************************************

// Loop function
void loop() {

}

//************************************************************************************************************

//************************************************************************************************************

// Error function (DON'T DELETE THIS)
void error(String message) {
        Serial.print(message);
        while (true)
                ;
}

//************************************************************************************************************
