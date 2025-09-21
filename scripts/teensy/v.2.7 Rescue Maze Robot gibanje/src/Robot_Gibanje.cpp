#include "Robot_Gibanje.h"

// Object definitions
VL53L0XsAnalog lidar; // LIDAR object
Adafruit_BNO055 gyroscope = Adafruit_BNO055(55); // Gyroscope object


const float Maze_Plate_Lenght=300;                            //Dimensions of maze palte
const float Snesor_Distance_From_Robot_Center_Point= 67.167;  //Distance from axis of robot center point circuit design 
const float Check_Walls_Distance=300;                         //Variable for checking is walls opend
const float Stop_Distance_For_Center_Robot=(Maze_Plate_Lenght/2)-Snesor_Distance_From_Robot_Center_Point ;           //Distance for center robot
const float Stop_Distance= Maze_Plate_Lenght/5;               //Distance use in autonomus movement for stopping robot if wall is to closed

/////////PID parameters for Go_Forward///////////////
double Setpoint1 ; // will be the desired value
double Input1; //
double Output1 ; //
bool Margina1;  // ako je prva ocitana vrijednost izmedju 0 i 180 daje true, 180-360 false
double Kp1=5, Ki1=1.5,  Kd1=0.85;
PID PID_Forward(&Input1, &Output1, &Setpoint1, Kp1, Ki1, Kd1, DIRECT);
////////////////////////////////////////////////////

/////////PID parameters for Go_Back///////////////
double Setpoint2 ; // will be the desired value
double Input2; //
double Output2 ; //
bool Margina2;  // ako je prva ocitana vrijednost izmedju 0 i 180 daje true, 180-360 false
double Kp2=5, Ki2=1.5,  Kd2=0.85;
PID PID_Back(&Input2, &Output2, &Setpoint2, Kp2, Ki2, Kd2, DIRECT);
////////////////////////////////////////////////////


ROBOT_GIBANJE::ROBOT_GIBANJE(){  // Constructor
}
ROBOT_GIBANJE::~ROBOT_GIBANJE(){ // Destructor
}

void ROBOT_GIBANJE::SetupZaSveKomponente(){

        delay(1000);

        Serial.println("We are inside SetupZaSveKomponente() function.");

        lidar.add(FORWARD1_AN_PIN);  // 0, Analog input Teensy pin 14, connected to LIDAR's AN input
        Serial.println("Added FORWARD1_AN_PIN lidar.");

        lidar.add(FORWARD2_AN_PIN);  //
        Serial.println("Added FORWARD2_AN_PIN lidar.");

        lidar.add(FORWARD3_AN_PIN);  //
        Serial.println("Added FORWARD3_AN_PIN lidar.");

        lidar.add(LEFT1_AN_PIN);     // 1, Analog input Teensy pin 15, connected to LIDAR's AN input
        Serial.println("Added LEFT1_AN_PIN lidar.");

        lidar.add(LEFT2_AN_PIN);     // 2, Analog input Teensy pin 16, connected to LIDAR's AN input
        Serial.println("Added LEFT2_AN_PIN lidar.");

        lidar.add(RIGHT1_AN_PIN);    // 3, Analog input Teensy pin 15, connected to LIDAR's AN input
        Serial.println("Added RIGHT1_AN_PIN lidar.");

        lidar.add(RIGHT2_AN_PIN);    // 4, Analog input Teensy pin 16, connected to LIDAR's AN input
        Serial.println("Added RIGHT2_AN_PIN lidar.");

        lidar.add(BACK1_AN_PIN);     //
        Serial.println("Added BACK1_AN_PIN lidar.");

        lidar.add(BACK2_AN_PIN);     //
        Serial.println("Added BACK2_AN_PIN lidar.");

        lidar.add(BACK3_AN_PIN);     //
        Serial.println("Added BACK3_AN_PIN lidar.");


        pinMode(THERMAL_OUT_PIN, INPUT); // Analog input pin 50, connected to thermal sensor OUT output

       
        PID_Forward.SetMode(AUTOMATIC);
        PID_Forward.SetOutputLimits(-40,40);

        PID_Back.SetMode(AUTOMATIC);
        PID_Back.SetOutputLimits(-40,40);

        pinMode(SPEED_LEFT_MOTOR_PIN, OUTPUT);
        pinMode(DIRECTION_LEFT_MOTOR_PIN, OUTPUT);
        pinMode(SPEED_RIGHT_MOTOR_PIN, OUTPUT);
        pinMode(DIRECTION_RIGHT_MOTOR_PIN, OUTPUT);

        pinMode(ELECTROMAGNET_PIN1, OUTPUT);
        pinMode(ELECTROMAGNET_PIN2, OUTPUT);

        

        if(!gyroscope.begin())
        {
                 // There was a problem detecting the BNO055 ... check your connections  
                Serial.print(F("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!"));
                
                 
                while(1);
        }
        delay(1000);
        gyroscope.setExtCrystalUse(true);

    


        
        Serial.println("Serijska komunikacija uspostavljena");
        Serial.println("######################################################");

}



void ROBOT_GIBANJE::SetMotorSpeedAndDirection(uint8_t SPEED_PIN, uint8_t DIRECTION_PIN, int motor_speed){

        if((motor_speed >= (-100))&&(motor_speed <= 100)) { // motor_speed needs to be from -100 to 100
                if(motor_speed > 0) {                             // when this number is negative motor goes forward, when negative it goes backwards
                        motor_speed = map(motor_speed,0,100,0,255);
                        digitalWrite(DIRECTION_PIN, LOW);
                        analogWrite(SPEED_PIN, motor_speed);
                }
                else if(motor_speed < 0) {
                        motor_speed = map(motor_speed,-100,0,0,255);
                        digitalWrite(DIRECTION_PIN, HIGH);
                        analogWrite(SPEED_PIN, motor_speed);
                }
                else {
                        analogWrite(DIRECTION_PIN, 0);
                        analogWrite(SPEED_PIN, 0);
                }
        }

}

void ROBOT_GIBANJE::Go_Forward(int motor_speed ){ // Default speed is maximum when you don't send any value to function

        Input1 = Read_Heading(); //Return orientation toward X axis

        if(Margina1)
        {
                if(Input1 < 361 && Input1 > 270)
                Input1 = -360 + Input1;
        }
        else
        {
                if(Input1 > -1 && Input1 <90)
                Input1 = 360 + Input1;
        }

        PID_Forward.Compute();//  PID_Forward.Compute();


        SetMotorSpeedAndDirection(SPEED_LEFT_MOTOR_PIN, DIRECTION_LEFT_MOTOR_PIN, motor_speed + Output1);
        SetMotorSpeedAndDirection(SPEED_RIGHT_MOTOR_PIN, DIRECTION_RIGHT_MOTOR_PIN, motor_speed - Output1);
        // Serial.println("Go_Forward() function is called.");

}


void ROBOT_GIBANJE::Go_Back(int motor_speed ){ // Default speed is maximum when you don't send any value to function

        Input2 = Read_Heading(); //Return orientation toward X axis

        if(Margina2)
        {
                if(Input2 < 361 && Input2 > 270)
                Input2 = -360 + Input2;
        }
        else
        {
                if(Input2 > -1 && Input2 <90)
                Input2 = 360 + Input2;
        }

        PID_Back.Compute();

        SetMotorSpeedAndDirection(SPEED_LEFT_MOTOR_PIN, DIRECTION_LEFT_MOTOR_PIN, motor_speed + Output2);
        SetMotorSpeedAndDirection(SPEED_RIGHT_MOTOR_PIN, DIRECTION_RIGHT_MOTOR_PIN, motor_speed - Output2);
        // Serial.println("Go_Back() function is called.");

}

void ROBOT_GIBANJE::Go_Left(int motor_speed ){ // Default speed is maximum when you don't send any value to function

        SetMotorSpeedAndDirection(SPEED_LEFT_MOTOR_PIN, DIRECTION_LEFT_MOTOR_PIN, -motor_speed);
        SetMotorSpeedAndDirection(SPEED_RIGHT_MOTOR_PIN, DIRECTION_RIGHT_MOTOR_PIN, motor_speed);
        // Serial.println("Go_Left() function is called.");

}

void ROBOT_GIBANJE::Go_Right(int motor_speed ){ // Default speed is maximum when you don't send any value to function

        SetMotorSpeedAndDirection(SPEED_LEFT_MOTOR_PIN, DIRECTION_LEFT_MOTOR_PIN, motor_speed);
        SetMotorSpeedAndDirection(SPEED_RIGHT_MOTOR_PIN, DIRECTION_RIGHT_MOTOR_PIN, -motor_speed);
        // Serial.println("Go_Right() function is called.");

}

void ROBOT_GIBANJE::Stop_Robot(){

        SetMotorSpeedAndDirection(SPEED_LEFT_MOTOR_PIN, DIRECTION_LEFT_MOTOR_PIN, 0);
        SetMotorSpeedAndDirection(SPEED_RIGHT_MOTOR_PIN, DIRECTION_RIGHT_MOTOR_PIN, 0);
        // Serial.println("Stop_Robot() function is called.");

}

uint16_t ROBOT_GIBANJE::Read_Forward_Left_Distance(){
        return lidar.distance(0);
}

uint16_t ROBOT_GIBANJE::Read_Forward_Medium_Distance(){
        return lidar.distance(1);
}

uint16_t ROBOT_GIBANJE::Read_Forward_Right_Distance(){
        return lidar.distance(2);
}

uint16_t ROBOT_GIBANJE::Read_Left_Back_Distance(){
        return lidar.distance(3);
}

uint16_t ROBOT_GIBANJE::Read_Left_Front_Distance(){
        return lidar.distance(4);
}

uint16_t ROBOT_GIBANJE::Read_Right_Back_Distance(){
        return lidar.distance(5);
}

uint16_t ROBOT_GIBANJE::Read_Right_Front_Distance(){
        return lidar.distance(6);
}

uint16_t ROBOT_GIBANJE::Read_Back_Left_Distance(){
        return lidar.distance(7);
}

uint16_t ROBOT_GIBANJE::Read_Back_Medium_Distance(){
        return lidar.distance(8);
}

uint16_t ROBOT_GIBANJE::Read_Back_Right_Distance(){
        return lidar.distance(9);
}

void ROBOT_GIBANJE::Read_All_Distances(){

        for(int i = 0; i < MAX_VL53L0XS_ANALOG; i++) {
                Distance_Array[i] = lidar.distance(i);
        }

}

uint16_t ROBOT_GIBANJE::Test_All_Distance_Sensors_One_By_One(int sensor_number){
if (sensor_number==0)
{
Serial.print("Prednji lijevi: ");
Serial.println(Read_Forward_Left_Distance());
delay(1000);
}
else if (sensor_number==1)
{
Serial.print("Prednji srednji: ");
Serial.println(Read_Forward_Medium_Distance());
delay(1000);
}
else if (sensor_number==2)
{
Serial.print("Prednji desni: ");
Serial.println( Read_Forward_Right_Distance());
delay(1000);
}
else if (sensor_number==3)
{
Serial.print("Lijevi zadnji: ");
Serial.println(Read_Left_Back_Distance());
delay(1000);
}
else if (sensor_number==4)
{
Serial.print("Lijevi prednji: ");
Serial.println(Read_Left_Front_Distance());
delay(1000);
}
else if (sensor_number==5)
{
Serial.print("Desni zadnji: ");
Serial.println( Read_Right_Back_Distance());
delay(1000);   
}
else if (sensor_number==6)
{
Serial.print("Desni prednji: ");
Serial.println(Read_Right_Front_Distance());
delay(1000);
}
else if (sensor_number==7)
{
Serial.print("Zadnji lijevi: ");
Serial.println(Read_Back_Left_Distance());
delay(1000);
}
else if (sensor_number==8)
{
Serial.print("Zadnji srednji: ");
Serial.println(Read_Back_Medium_Distance());
delay(1000); 
}
else if (sensor_number==9)
{
Serial.print("Zadnji desni: ");
Serial.println(Read_Back_Right_Distance());
delay(1000);   
}

}

void ROBOT_GIBANJE::Go_Forward_30cm(int motor_speed ){ // Default speed is maximum when you don't send any value to function

        uint16_t first_distance = Read_Forward_Medium_Distance();
        // Serial.println(first_distance);
        if(first_distance > 335){
        uint16_t allowed_error = 0; // This number can be changed to achieve correct movement

        Setpoint1 = Read_Heading(); //Return orientation toward X axis

        if(Setpoint1<=180)    // da li se nalazi u 1. i 4. kvadrantu ili 2. i 3. kvadrantu
              {
               Margina1 = true;
              }
              else
              Margina1 = false;


        while(Read_Forward_Medium_Distance() > (first_distance - 300 + allowed_error)) { // -300 da ide za 30 cm unaprijed
                Go_Forward(motor_speed);
                // Serial.println(Read_Forward_Distance());
        }
        Stop_Robot();
        // Serial.println("Go_Forward_30cm() function is called.");
        }

}

void ROBOT_GIBANJE::Go_Back_30cm(int motor_speed ){

        uint16_t first_distance = Read_Forward_Medium_Distance();

        // Serial.println(first_distance);
        uint16_t allowed_error = 0; // This number can be changed to achieve correct movement

        Setpoint2 = Read_Heading(); //Return orientation toward X axis

        if(Setpoint2<=180)    // da li se nalazi u 1. i 4. kvadrantu ili 2. i 3. kvadrantu
              {
                Margina2 = true;   
              }
              else
                Margina2 = false;

        while(Read_Forward_Medium_Distance() < (first_distance + 300 - allowed_error)) {
                Go_Back(motor_speed);
                // Serial.println(Read_Forward_Distance());
        }
        Stop_Robot();
        // Serial.println("Go_Back_30cm() function is called.");

}

float ROBOT_GIBANJE::Read_Heading(){  //Return orientation toward X axis

        sensors_event_t event;
        gyroscope.getEvent(&event);
        //Serial.println("Temporary robot orientation toward X axis is: ");
        //Serial.println(event.orientation.x);
        return event.orientation.x;

}

// When going right angle is increasing from 0 to 360
void ROBOT_GIBANJE::Go_Right_90degrees(int motor_speed ){ // Default speed for turning right is 30, when you don't send any value to function

        uint16_t initial_heading = Read_Heading(); //Return orientation toward X axis
        uint8_t allowed_error = 5; // This number can be changed to achieve precise turns
        if(initial_heading < 270) {
                while(Read_Heading() < (initial_heading + 90 - allowed_error)) {
                        Go_Right(motor_speed);
                }
        }
        else{
                while((Read_Heading() <= 360) && (Read_Heading() >= 270)) {
                        Go_Right(motor_speed);
                }
                while(Read_Heading() < (initial_heading - 270 - allowed_error)) {
                        Go_Right(motor_speed);
                }
        }
        Stop_Robot();
        // Serial.println("Go_Right_90degrees() function is called.");

}

// When going left angle is decreasing from 360 to 0
void ROBOT_GIBANJE::Go_Left_90degrees(int motor_speed ){ // Default speed for turning left is 30, when you don't send any value to function

        uint16_t initial_heading = Read_Heading();
        uint8_t allowed_error = 5; // This number can be changed to achieve precise turns
        if(initial_heading > 90) {
                while(Read_Heading() > (initial_heading - 90 + allowed_error)) {
                        Go_Left(motor_speed);
                }
        }
        else{
                while((Read_Heading() >= 0) && (Read_Heading() <= 90)) {
                        Go_Left(motor_speed);
                }
                while(Read_Heading() > (initial_heading + 270 + allowed_error)) {
                        Go_Left(motor_speed);
                }
        }
        Stop_Robot();
        // Serial.println("Go_Left_90degrees() function is called.");

}

void ROBOT_GIBANJE::Go_Left_180degrees(int motor_speed ){




}

uint16_t ROBOT_GIBANJE::Read_Temperature(){
        return map(analogRead(THERMAL_OUT_PIN), 0, 52851, -20, 100);
}

bool ROBOT_GIBANJE::Is_Wall_Left(){
         if ((Read_Left_Back_Distance() || Read_Left_Front_Distance())<(Check_Walls_Distance)) return true;
        else return false;
}
bool ROBOT_GIBANJE::Is_Wall_Right(){
        if ((Read_Right_Back_Distance() || Read_Right_Front_Distance())<(Check_Walls_Distance)) return true;
        else return false;
}
bool ROBOT_GIBANJE::Is_Wall_Forward(){
        if ((Read_Forward_Left_Distance() || Read_Forward_Medium_Distance() || Read_Forward_Right_Distance())<(Check_Walls_Distance)) return true;
        else return false;
}
bool ROBOT_GIBANJE::Is_Wall_Back(){
        if ((Read_Back_Left_Distance() || Read_Back_Medium_Distance() || Read_Back_Right_Distance())<(Check_Walls_Distance)) return true;
        else return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool ROBOT_GIBANJE::Moveing_Is_Wall_Opend_Left(){
         if ((Read_Left_Back_Distance() && Read_Left_Front_Distance())>(Check_Walls_Distance)) return true;
        else return false;
}
bool ROBOT_GIBANJE::Moveing_Is_Wall_Opend_Right(){
        if ((Read_Right_Back_Distance() && Read_Right_Front_Distance())>(Check_Walls_Distance)) return true;
        else return false;
}
bool ROBOT_GIBANJE::Moveing_Is_Wall_Opend_Forward(){
        if ((Read_Forward_Left_Distance() && Read_Forward_Medium_Distance() && Read_Forward_Right_Distance())>(Check_Walls_Distance)) return true;
        else return false;
}
bool ROBOT_GIBANJE::Moveing_Is_Wall_Opend_Back(){
        if ((Read_Back_Left_Distance() && Read_Back_Medium_Distance() && Read_Back_Right_Distance())>(Check_Walls_Distance)) return true;
        else return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool ROBOT_GIBANJE::Moveing_Is_Wall_Left(){
         if ((Read_Left_Back_Distance() && Read_Left_Front_Distance())<(Stop_Distance)) return true;
        else return false;
}
bool ROBOT_GIBANJE::Moveing_Is_Wall_Right(){
        if ((Read_Right_Back_Distance() && Read_Right_Front_Distance())<(Stop_Distance)) return true;
        else return false;
}
bool ROBOT_GIBANJE::Moveing_Is_Wall_Forward(){
        if ((Read_Forward_Left_Distance() && Read_Forward_Medium_Distance() && Read_Forward_Right_Distance())<(Stop_Distance)) return true;
        else return false;
}
bool ROBOT_GIBANJE::Moveing_Is_Wall_Back(){
        if ((Read_Back_Left_Distance() && Read_Back_Medium_Distance() && Read_Back_Right_Distance())<(Stop_Distance)) return true;
        else return false;
}

void ROBOT_GIBANJE::Push_Box(){
        digitalWrite(ELECTROMAGNET_PIN1, LOW);
        digitalWrite(ELECTROMAGNET_PIN2, HIGH);
        delay(2000);
        digitalWrite(ELECTROMAGNET_PIN1, LOW);
        digitalWrite(ELECTROMAGNET_PIN2, LOW);
}

void error(String message) {    // error message za VL53L0XsAnalog

        Serial.print(message);
        while (true)
                ;
}

void ROBOT_GIBANJE::Find_and_Align_Left_Wall(){ 
uint16_t Current_Left_Front_Distance= Read_Left_Front_Distance();
uint16_t Current_Left_Back_Distance= Read_Left_Back_Distance();
uint16_t Alowed_Error= 5; //This two sensors values need to be very closed because we want precise robot alignment toward left wall
 
while(((Current_Left_Front_Distance - Current_Left_Back_Distance)>Alowed_Error) || ((Current_Left_Front_Distance - Current_Left_Back_Distance)<(-Alowed_Error)) ){
        Go_Left();
        Serial.println("We are trying to allign robot left side...");
        }
Serial.println("Robot is alligned with left side.");

//First break point

/*
############################## PSEUDO CODE ############################## 
1.Rotate
2.When two left sensors have similar distances, stop rotating
#########################################################################
*/
}

void ROBOT_GIBANJE::Center_Robot(){ 
if (Moveing_Is_Wall_Forward()) Serial.println("Robot front side is oriented toward closed  maze side.");

else if(Moveing_Is_Wall_Back()){
        Go_Left_180degrees();
        Serial.println("Rotating left for 180 degrees...Robot front side is oriented toward closed  maze side.");
}

else if(Moveing_Is_Wall_Left()){
        Go_Left_90degrees();
        Serial.println("Rotating left for 90 degrees...Robot front side is oriented toward closed  maze side.");
}

else if(Moveing_Is_Wall_Right()){
        Go_Right_90degrees();
        Serial.println("Rotating right for 90 degrees...Robot front side is oriented toward closed  maze side.");
}
//else Serial.println("Maybe make function for rotation of 45 degrees is else case!?");DrzacZaBateriju
//Second break point



while (!Moveing_Is_Wall_Forward())
{
       Go_Forward();
} 

/*
############################## PSEUDO CODE ############################## 
1.Rotate robot toward closed wall
2.Go forward or backward and stop when needed distance (Moveing_Is_Wall_Forward()) is found
3.Find closed wall which is +-90 degrees oriented toward wall founded in first step
4.Go forward or backward and stop when needed distance (Moveing_Is_Wall_Forward()) is found
#########################################################################
*/

}

void ROBOT_GIBANJE::Find_and_Rotate_To_Opend_Wall(){ 
/*
if (( Read_Forward_Left_Distance() && Read_Forward_Medium_Distance() && Read_Forward_Right_Distance()) > Check_Walls_Distance) Serial.println("Robot front side is oriented toward opened  maze side.");

else if((Read_Back_Left_Distance() && Read_Back_Medium_Distance() && Read_Back_Right_Distance()) > Check_Walls_Distance ){
        Go_Left_180degrees();
        Serial.println("Rotating left for 180 degrees...Robot front side is oriented toward opened  maze side.");
}

else if((Read_Left_Back_Distance() && Read_Left_Front_Distance()) > Check_Walls_Distance ){
        Go_Left_90degrees();
        Serial.println("Rotating left for 90 degrees...Robot front side is oriented toward opened  maze side.");
}

else if((Read_Right_Back_Distance() && Read_Right_Front_Distance()) > Check_Walls_Distance ){
        Go_Right_90degrees();
        Serial.println("Rotating right for 90 degrees...Robot front side is oriented toward opened  maze side.");
}

else Serial.println("Maybe make functio for rotation of 45 degrees!?");
*/

if (Moveing_Is_Wall_Opend_Forward()) Serial.println("Robot front side is oriented toward opened  maze side.");

else if(Moveing_Is_Wall_Opend_Back()){
        Go_Left_180degrees();
        Serial.println("Rotating left for 180 degrees...Robot front side is oriented toward opened  maze side.");
}

else if(Moveing_Is_Wall_Opend_Left()){
        Go_Left_90degrees();
        Serial.println("Rotating left for 90 degrees...Robot front side is oriented toward opened  maze side.");
}

else if(Moveing_Is_Wall_Opend_Right()){
        Go_Right_90degrees();
        Serial.println("Rotating right for 90 degrees...Robot front side is oriented toward opened  maze side.");
}

else Serial.println("Maybe make function for rotation of 45 degrees in else case!?");

//Seconde break point


/*
############################## PSEUDO CODE ############################## 
1.Robot stays od the place and try to find opend maze side with distance sensor
2.Rotate robot toward opend side
#########################################################################
*/
 
}

void ROBOT_GIBANJE::Automomus_Maze_Path_Finding(){

while(Moveing_Is_Wall_Forward()){ 
        Go_Forward_30cm();
        Serial.println("Going forward to the first wall.");
        }

Find_and_Rotate_To_Opend_Wall();



}

