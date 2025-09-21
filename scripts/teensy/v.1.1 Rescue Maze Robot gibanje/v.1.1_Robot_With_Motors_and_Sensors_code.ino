
// Uncomment line below if you use Platformio IDE
//#include <Arduino.h>

#include <boarddefs.h>
#include <IRremote.h>
#include <IRremoteInt.h>
#include <ir_Lego_PF_BitStreamEncoder.h>

//************************************************************************************************************

//Pins definiton
#define SPEED_MOTOR_1_PIN     2    // 1. motor, pin za brzinu motora
#define DIRECTION_MOTOR_1_PIN 3    // 1. motor, pin za smjer vrtnje motora
#define SPEED_MOTOR_2_PIN     4    // 2. motor, pin za brzinu motora
#define DIRECTION_MOTOR_2_PIN 5    // 2. motor, pin za smjer vrtnje motora
#define SPEED_MOTOR_3_PIN     6    // 3. motor, pin za brzinu motora
#define DIRECTION_MOTOR_3_PIN 7    // 3. motor, pin za smjer vrtnje motora
#define SPEED_MOTOR_4_PIN     8    // 4. motor, pin za brzinu motora
#define DIRECTION_MOTOR_4_PIN 9    // 4. motor, pin za smjer vrtnje motora
#define IR_RECV_PIN           10   // digital pin used to connect the IR receiver sensor
 
#define IR_ADVANCE         0x00FF18E7       //code from IR controller "▲" button
#define IR_BACK            0x00FF4AB5       //code from IR controller "▼" button
#define IR_RIGHT           0x00FF5AA5       //code from IR controller ">" button
#define IR_LEFT            0x00FF10EF       //code from IR controller "<" button
#define IR_STOP            0x00FF38C7       //code from IR controller "OK" button
#define IR_AUTONOMUS_MODE  0x00FFB04F       //code from IR controller "#" button

//Distance sensor pin, collects data from an analog sensor
int DISTANCE_SENSOR_1_PIN = 35;             // analog pin used to connect the distance sensor

//Gyroscope sensor pins, collects data from an analog sensor
int GIROSCOPE_YAW_PIN = 36;                 // analog pin used to connect to the gyroscope sensor
int GIROSCOPE_R0LL_PIN = 37;  
int GIROSCOPE_PITCH_PIN= 38;  

//Temperature sensor pin, collects data from an analog sensor
int TEMPERATURE_SENSOR_1_PIN = 39;          // analog pin used to connect the temperature sensor

//************************************************************************************************************

//Variable definition
int SPEED_TRUE=255;
int SPEED_FALSE=0;
int DIRECTION_TRUE=255;
int DIRECTION_FALSE=0;

//Distance sensor value variable, variable to store the values from sensor(initially zero
int DISTANCE_VALUE_SENSOR_1 = 0;  

//Gyroscope sensor value variables, variable to store the values from sensor(initially zero
int GIROSCOPE_ROLL_VALUE = 0;         // X-axis  
int GIROSCOPE_PITCH_VALUE= 0;         // Y-axis
int GIROSCOPE_YAW_VALUE = 0;          // Z-axis

//Temperature sensor value variable, variable to store the values from sensor(initially zero
int TEMPERATURE_VALUE_SENSOR_1 = 0; 

// IR sensor variables  
IRrecv IR_DECODER_VAR(IR_RECV_PIN);   //Decoder varable
decode_results IR_RESULT;             //Store varable

//************************************************************************************************************

// Function prototypes
void Go_Forward();
void Go_Back();
void Stop_Robot();
void Simple_Robot_Moveing();
int Measure_Gyroscope_Angles( int *GIROSCOPE_ROLL_VALUE,int *GIROSCOPE_PITCH_VALUE,int *GIROSCOPE_YAW_VALUE);
int Measure_Distance( int sensor_name_pin, int sensor_value_variable);
int Measure_Temperature( int sensor_name_pin, int sensor_value_variable);

//************************************************************************************************************

// Functions definition

void Go_Forward(){

digitalWrite(DIRECTION_MOTOR_1_PIN, DIRECTION_FALSE);  
digitalWrite(SPEED_MOTOR_1_PIN, SPEED_TRUE);  

digitalWrite(DIRECTION_MOTOR_2_PIN, DIRECTION_FALSE);  
digitalWrite(SPEED_MOTOR_2_PIN , SPEED_TRUE);  

digitalWrite(DIRECTION_MOTOR_3_PIN, DIRECTION_FALSE);  
digitalWrite(SPEED_MOTOR_3_PIN, SPEED_TRUE);  

digitalWrite(DIRECTION_MOTOR_4_PIN, DIRECTION_FALSE);  
digitalWrite(SPEED_MOTOR_4_PIN, SPEED_TRUE); 

Serial.println(" Go_Forward() function is called.");

}


void Go_Back(){

digitalWrite(DIRECTION_MOTOR_1_PIN, DIRECTION_TRUE);  
digitalWrite(SPEED_MOTOR_1_PIN, SPEED_FALSE);  

digitalWrite(DIRECTION_MOTOR_2_PIN, DIRECTION_TRUE);  
digitalWrite(SPEED_MOTOR_2_PIN , SPEED_FALSE);  

digitalWrite(DIRECTION_MOTOR_3_PIN, DIRECTION_TRUE);  
digitalWrite(SPEED_MOTOR_3_PIN, SPEED_FALSE);  

digitalWrite(DIRECTION_MOTOR_4_PIN, DIRECTION_TRUE);  
digitalWrite(SPEED_MOTOR_4_PIN, SPEED_FALSE); 

Serial.println(" Go_Back() function is called.");

}

void Stop_Robot(){

digitalWrite(DIRECTION_MOTOR_1_PIN, DIRECTION_FALSE);  
digitalWrite(SPEED_MOTOR_1_PIN, SPEED_FALSE);  

digitalWrite(DIRECTION_MOTOR_2_PIN, DIRECTION_FALSE);  
digitalWrite(SPEED_MOTOR_2_PIN , SPEED_FALSE);  

digitalWrite(DIRECTION_MOTOR_3_PIN, DIRECTION_FALSE);  
digitalWrite(SPEED_MOTOR_3_PIN, SPEED_FALSE);  

digitalWrite(DIRECTION_MOTOR_4_PIN, DIRECTION_FALSE);  
digitalWrite(SPEED_MOTOR_4_PIN, SPEED_FALSE);  

Serial.println(" Stop_Robot() function is called.");

}

void Simple_Robot_Moveing(){

Go_Forward();
delay(5000);
Go_Back();
delay(5000);
Stop_Robot();
delay(5000);

}

int Measure_Gyroscope_Angles( int *GIROSCOPE_ROLL_VALUE, int *GIROSCOPE_PITCH_VALUE, int *GIROSCOPE_YAW_VALUE){

// reads the value of the gyroscope sensor
*GIROSCOPE_ROLL_VALUE = analogRead(GIROSCOPE_R0LL_PIN ); 
*GIROSCOPE_PITCH_VALUE = analogRead(GIROSCOPE_PITCH_PIN); 
*GIROSCOPE_YAW_VALUE = analogRead(GIROSCOPE_YAW_PIN);  

// prints the value of the sensor  

Serial.print(" Rotacija po X-osi: ");
Serial.print(*GIROSCOPE_ROLL_VALUE); 
Serial.print(",");  
Serial.print(" Y-osi:  "); 
Serial.print(*GIROSCOPE_PITCH_VALUE);  
Serial.print(",");  
Serial.print(" Z-osi:  "); 
Serial.print(*GIROSCOPE_YAW_VALUE);            
Serial.println(" degree.");


}

int Measure_Distance( int sensor_name_pin, int sensor_value_variable){

sensor_name_pin = analogRead(sensor_value_variable);
Serial.print("Udaljenost: ");                           // reads the value of the sharp sensor
Serial.print(sensor_name_pin/2);                        // prints the value of the sensor to the serial monitor
Serial.println(" cm.");
return (sensor_name_pin/2 ); 
 
}

int Measure_Temperature( int sensor_name_pin, int sensor_value_variable){

sensor_value_variable = analogRead(sensor_name_pin);     // reads the value of the temperature sensor
Serial.print("Temperatura: ");                    
Serial.print( sensor_value_variable );                   // prints the value of the  temperature sensor to the serial monitor
Serial.println(" Celsius degree."); 
return sensor_value_variable;

}

//************************************************************************************************************

void setup() {

Serial.begin(9600);                          // starts the serial monitor

IR_DECODER_VAR.enableIRIn();                 // Make decoder variable enable

pinMode(SPEED_MOTOR_1_PIN, OUTPUT);
pinMode(DIRECTION_MOTOR_1_PIN, OUTPUT); 

pinMode(SPEED_MOTOR_2_PIN , OUTPUT);
pinMode(DIRECTION_MOTOR_2_PIN, OUTPUT); 

pinMode(SPEED_MOTOR_3_PIN, OUTPUT);
pinMode(DIRECTION_MOTOR_3_PIN, OUTPUT); 

pinMode(SPEED_MOTOR_4_PIN, OUTPUT);
pinMode(DIRECTION_MOTOR_4_PIN, OUTPUT); 


}

//************************************************************************************************************

void loop() {
/*
Simple_Robot_Moveing();
Measure_Distance( DISTANCE_SENSOR_1_PIN, DISTANCE_VALUE_SENSOR_1);
Measure_Temperature(TEMPERATURE_SENSOR_1_PIN, TEMPERATURE_VALUE_SENSOR_1);
Measure_Gyroscope_Angles( &GIROSCOPE_ROLL_VALUE, &GIROSCOPE_PITCH_VALUE, &GIROSCOPE_YAW_VALUE);
//By pointer eturned gyroscope variables 
int x_axsis= GIROSCOPE_ROLL_VALUE;
int y_axsis= GIROSCOPE_PITCH_VALUE;
int z_axsis= GIROSCOPE_YAW_VALUE;
*/
 if (IR_DECODER_VAR.decode(&IR_RESULT)){

      if(IR_RESULT.value==IR_ADVANCE){
      Go_Forward();
      }
      
      else if(IR_RESULT.value==IR_BACK){
      Go_Back();
      }
      
      else if(IR_RESULT.value==IR_LEFT ){
      Serial.println("LEFT");
      }
      
      else if(IR_RESULT.value==IR_RIGHT){
      Serial.println("RIGHT");
      }
      
      else if(IR_RESULT.value==IR_STOP){
      Stop_Robot();
      }

      else if(IR_RESULT.value==IR_AUTONOMUS_MODE){
      Serial.println("AUTONOMUS_MODE");
      }

      IR_RESULT.value=0;
      IR_DECODER_VAR.resume();
  }


}
