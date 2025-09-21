#include "Robot_Gibanje.h"

// Object definitions
VL53L0XsAnalog lidar; // LIDAR object
Adafruit_BNO055 gyroscope = Adafruit_BNO055(55); // Gyroscope object


/////////PID parameters///////////////
double Setpoint ; // will be the desired value
double Input; //
double Output ; //
bool Margina;  // ako je prva ocitana vrijednost izmedju 0 i 180 daje true, 180-360 false
double Kp=5, Ki=1.5,  Kd=0.85;
PID myPID( &Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);
//////////////////////////////////////

ROBOT_GIBANJE::ROBOT_GIBANJE(){
}
ROBOT_GIBANJE::~ROBOT_GIBANJE(){
}



void ROBOT_GIBANJE::SetupZaSveKomponente(){

        lidar.add(LIDAR1_AN_PIN); // Analog input Teensy pin 14, connected to LIDAR's AN input
        lidar.add(LIDAR2_AN_PIN); // Analog input Teensy pin 15, connected to LIDAR's AN input
        lidar.add(LIDAR3_AN_PIN); // Analog input Teensy pin 16, connected to LIDAR's AN input

        pinMode(THERMAL_OUT_PIN, INPUT); // Analog input pin 50, connected to thermal sensor OUT output

        myPID.SetMode(AUTOMATIC);
        myPID.SetOutputLimits(-40,40);

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


Serial.println("Serijska komunikacija uspostavljena");

}



void ROBOT_GIBANJE::SetMotorSpeedAndDirection(uint8_t SPEED_PIN, uint8_t DIRECTION_PIN, int speed_and_direction){

        if((speed_and_direction >= (-100))&&(speed_and_direction <= 100)) { // speed_and_direction needs to be from -100 to 100
                if(speed_and_direction > 0) {                             // when this number is negative motor goes forward, when negative it goes backwards
                        speed_and_direction = map(speed_and_direction,0,100,0,255);
                        digitalWrite(DIRECTION_PIN, LOW);
                        analogWrite(SPEED_PIN, speed_and_direction);
                }
                else if(speed_and_direction < 0) {
                        speed_and_direction = map(speed_and_direction,-100,0,0,255);
                        digitalWrite(DIRECTION_PIN, HIGH);
                        analogWrite(SPEED_PIN, speed_and_direction);
                }
                else {
                        analogWrite(DIRECTION_PIN, 0);
                        analogWrite(SPEED_PIN, 0);
                }
        }

}

void ROBOT_GIBANJE::Go_Forward(int speed_and_direction ){ // Default speed is maximum when you don't send any value to function

Input = Read_Heading() ;

if(Margina)
{
if(Input < 361 && Input > 270)
Input = -360 + Input;
}
else
{
if(Input > -1 && Input <90)
Input = 360 + Input;
}

 myPID.Compute();//  myPID.Compute();


        SetMotorSpeedAndDirection(SPEED_MOTOR_1_PIN, DIRECTION_MOTOR_1_PIN, speed_and_direction + Output);
        SetMotorSpeedAndDirection(SPEED_MOTOR_2_PIN, DIRECTION_MOTOR_2_PIN, speed_and_direction - Output);
        // Serial.println("Go_Forward() function is called.");

}


void ROBOT_GIBANJE::Go_Back(int speed_and_direction ){ // Default speed is maximum when you don't send any value to function

        SetMotorSpeedAndDirection(SPEED_MOTOR_1_PIN, DIRECTION_MOTOR_1_PIN, speed_and_direction);
        SetMotorSpeedAndDirection(SPEED_MOTOR_2_PIN, DIRECTION_MOTOR_2_PIN, speed_and_direction);
        // Serial.println("Go_Back() function is called.");

}

void ROBOT_GIBANJE::Go_Left(int speed_and_direction ){ // Default speed is maximum when you don't send any value to function

        SetMotorSpeedAndDirection(SPEED_MOTOR_1_PIN, DIRECTION_MOTOR_1_PIN, -speed_and_direction);
        SetMotorSpeedAndDirection(SPEED_MOTOR_2_PIN, DIRECTION_MOTOR_2_PIN, speed_and_direction);
        // Serial.println("Go_Left() function is called.");

}

void ROBOT_GIBANJE::Go_Right(int speed_and_direction ){ // Default speed is maximum when you don't send any value to function

        SetMotorSpeedAndDirection(SPEED_MOTOR_1_PIN, DIRECTION_MOTOR_1_PIN, speed_and_direction);
        SetMotorSpeedAndDirection(SPEED_MOTOR_2_PIN, DIRECTION_MOTOR_2_PIN, -speed_and_direction);
        // Serial.println("Go_Right() function is called.");

}

void ROBOT_GIBANJE::Stop_Robot(){

        SetMotorSpeedAndDirection(SPEED_MOTOR_1_PIN, DIRECTION_MOTOR_1_PIN, 0);
        SetMotorSpeedAndDirection(SPEED_MOTOR_2_PIN, DIRECTION_MOTOR_2_PIN, 0);
        // Serial.println("Stop_Robot() function is called.");

}

void ROBOT_GIBANJE::Go_Forward_30cm(int speed_and_direction ){ // Default speed is maximum when you don't send any value to function

        uint16_t first_distance = lidar.distance();

        Serial.println(first_distance);
        uint16_t allowed_error = 0; // This number can be changed to achieve correct movement

        Setpoint = Read_Heading() ;

        if(Setpoint<=180)    // da li se nalazi u 1. i 4. kvadrantu ili 2. i 3. kvadrantu
              {
               Margina = true;
              }
              else
              Margina = false;


        while(lidar.distance() > (first_distance - 300 + allowed_error)) { // -300 da ide za 30 cm unaprijed
                Go_Forward(speed_and_direction);
                // Serial.println(lidar.distance());
        }
        Stop_Robot();
        // Serial.println("Go_Forward_30cm() function is called.");

}

void ROBOT_GIBANJE::Go_Back_30cm(int speed_and_direction ){

        uint16_t first_distance = lidar.distance();

        Serial.println(first_distance);
        uint16_t allowed_error = 0; // This number can be changed to achieve correct movement

        while(lidar.distance() < (first_distance + 300 - allowed_error)) {
                Go_Back(speed_and_direction);
                // Serial.println(lidar.distance());
        }
        Stop_Robot();
        // Serial.println("Go_Back_30cm() function is called.");

}

void ROBOT_GIBANJE::Read_All_Distances(){

        for(int i = 0; i < MAX_VL53L0XS_ANALOG; i++) {
                Distance_Array[i] = lidar.distance(i);
        }

}


float ROBOT_GIBANJE::Read_Heading(){

        sensors_event_t event;
        gyroscope.getEvent(&event);
        return event.orientation.x;

}

// When going right angle is increasing from 0 to 360
void ROBOT_GIBANJE::Go_Right_90degrees(int speed_and_direction ){ // Default speed for turning right is 20, when you don't send any value to function

        uint16_t initial_heading = Read_Heading();
        uint8_t allowed_error = 6; // This number can be changed to achieve precise turns
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
void ROBOT_GIBANJE::Go_Left_90degrees(int speed_and_direction ){ // Default speed for turning left is 20, when you don't send any value to function

        uint16_t initial_heading = Read_Heading();
        uint8_t allowed_error = 2; // This number can be changed to achieve precise turns
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

uint16_t ROBOT_GIBANJE::Read_Temperature(){

        return analogRead(THERMAL_OUT_PIN);

}

void error(String message) {    // error message za VL53L0XsAnalog

        Serial.print(message);
        while (true)
                ;
}
