#include "Robot_Gibanje.h"

// Object definitions
VL53L0XsAnalog lidar;                            // LIDAR object
Adafruit_BNO055 gyroscope = Adafruit_BNO055(55); // Gyroscope object

const float Maze_Plate_Lenght = 325;                                                                            //Dimensions of maze palte
const float Snesor_Distance_From_Robot_Center_Point = 67.167;                                                   //Distance from axis of robot center point circuit design
const float Stop_Distance_For_Center_Robot = (Maze_Plate_Lenght / 2) - Snesor_Distance_From_Robot_Center_Point; //Distance for center robot, Total=5 cm
const float Left_and_Right_Snesor_Distance_From_Robot_Center_Point = 9.8;
const float Critical_left_and_right_Distance = (Maze_Plate_Lenght / 2) - Left_and_Right_Snesor_Distance_From_Robot_Center_Point - 13; //Distance for wall folloving

const float Stop_Distance = Maze_Plate_Lenght / 5;
const float Check_Walls_Distance = 300; //Variable for checking is walls opend
                                        //Distance use in autonomus movement for stopping robot if wall is to closed

/////////PID parameters for Go_Forward///////////////
double Setpoint1; // will be the desired value
double Input1;    //
double Output1;   //
bool Margina1;    // ako je prva ocitana vrijednost izmedju 0 i 180 daje true, 180-360 false
double Kp1 = 5, Ki1 = 1.5, Kd1 = 0.85;
PID PID_Forward(&Input1, &Output1, &Setpoint1, Kp1, Ki1, Kd1, DIRECT);
////////////////////////////////////////////////////

/////////PID parameters for Go_Back///////////////
double Setpoint2; // will be the desired value
double Input2;    //
double Output2;   //
bool Margina2;    // ako je prva ocitana vrijednost izmedju 0 i 180 daje true, 180-360 false
double Kp2 = 5, Ki2 = 1.5, Kd2 = 0.85;
PID PID_Back(&Input2, &Output2, &Setpoint2, Kp2, Ki2, Kd2, DIRECT);
////////////////////////////////////////////////////

ROBOT_GIBANJE::ROBOT_GIBANJE()
{ // Constructor
}

ROBOT_GIBANJE::~ROBOT_GIBANJE()
{ // Destructor
}

void ROBOT_GIBANJE::SetupZaSveKomponente()
{

        delay(1000);

        Serial.println("We are inside SetupZaSveKomponente() function.");

        lidar.add(FORWARD1_AN_PIN); // 0, Analog input Teensy pin 14, connected to LIDAR's AN input
        Serial.println("Added FORWARD1_AN_PIN lidar.");

        lidar.add(FORWARD2_AN_PIN); //
        Serial.println("Added FORWARD2_AN_PIN lidar.");

        lidar.add(FORWARD3_AN_PIN); //
        Serial.println("Added FORWARD3_AN_PIN lidar.");

        lidar.add(LEFT1_AN_PIN); // 1, Analog input Teensy pin 15, connected to LIDAR's AN input
        Serial.println("Added LEFT1_AN_PIN lidar.");

        lidar.add(LEFT2_AN_PIN); // 2, Analog input Teensy pin 16, connected to LIDAR's AN input
        Serial.println("Added LEFT2_AN_PIN lidar.");

        lidar.add(RIGHT1_AN_PIN); // 3, Analog input Teensy pin 15, connected to LIDAR's AN input
        Serial.println("Added RIGHT1_AN_PIN lidar.");

        lidar.add(RIGHT2_AN_PIN); // 4, Analog input Teensy pin 16, connected to LIDAR's AN input
        Serial.println("Added RIGHT2_AN_PIN lidar.");

        lidar.add(BACK1_AN_PIN); //
        Serial.println("Added BACK1_AN_PIN lidar.");

        lidar.add(BACK2_AN_PIN); //
        Serial.println("Added BACK2_AN_PIN lidar.");

        lidar.add(BACK3_AN_PIN); //
        Serial.println("Added BACK3_AN_PIN lidar.");

        pinMode(THERMAL_OUT_PIN, INPUT); // Analog input pin 50, connected to thermal sensor OUT output

        PID_Forward.SetMode(AUTOMATIC);
        PID_Forward.SetOutputLimits(-40, 40);

        PID_Back.SetMode(AUTOMATIC);
        PID_Back.SetOutputLimits(-40, 40);

        pinMode(SPEED_LEFT_MOTOR_PIN, OUTPUT);
        pinMode(DIRECTION_LEFT_MOTOR_PIN, OUTPUT);
        pinMode(SPEED_RIGHT_MOTOR_PIN, OUTPUT);
        pinMode(DIRECTION_RIGHT_MOTOR_PIN, OUTPUT);

        pinMode(ELECTROMAGNET_PIN1, OUTPUT);
        pinMode(ELECTROMAGNET_PIN2, OUTPUT);

        if (!gyroscope.begin())
        {
                // There was a problem detecting the BNO055 ... check your connections
                Serial.print(F("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!"));

                while (1)
                        ;
        }
        delay(1000);
        gyroscope.setExtCrystalUse(true);

        Serial.println("Serijska komunikacija uspostavljena");
        Serial.println("######################################################");
}

void ROBOT_GIBANJE::SetMotorSpeedAndDirection(uint8_t SPEED_PIN, uint8_t DIRECTION_PIN, int motor_speed)
{

        if ((motor_speed >= (-100)) && (motor_speed <= 100))
        { // motor_speed needs to be from -100 to 100
                if (motor_speed > 0)
                { // when this number is negative motor goes forward, when negative it goes backwards
                        motor_speed = map(motor_speed, 0, 100, 0, 255);
                        digitalWrite(DIRECTION_PIN, LOW);
                        analogWrite(SPEED_PIN, motor_speed);
                }
                else if (motor_speed < 0)
                {
                        motor_speed = map(motor_speed, -100, 0, 0, 255);
                        digitalWrite(DIRECTION_PIN, HIGH);
                        analogWrite(SPEED_PIN, motor_speed);
                }
                else
                {
                        analogWrite(DIRECTION_PIN, 0);
                        analogWrite(SPEED_PIN, 0);
                }
        }
}

void ROBOT_GIBANJE::Go_Forward(int motor_speed)
{ // Default speed is maximum when you don't send any value to function

        Input1 = Read_Heading(); //Return orientation toward X axis

        if (Margina1)
        {
                if (Input1 < 361 && Input1 > 270)
                        Input1 = -360 + Input1;
        }
        else
        {
                if (Input1 > -1 && Input1 < 90)
                        Input1 = 360 + Input1;
        }

        PID_Forward.Compute(); //  PID_Forward.Compute();

        SetMotorSpeedAndDirection(SPEED_LEFT_MOTOR_PIN, DIRECTION_LEFT_MOTOR_PIN, motor_speed);
        SetMotorSpeedAndDirection(SPEED_RIGHT_MOTOR_PIN, DIRECTION_RIGHT_MOTOR_PIN, motor_speed);
        // Serial.println("Go_Forward() function is called.");
}

void ROBOT_GIBANJE::Go_Back(int motor_speed)
{ // Default speed is maximum when you don't send any value to function

        Input2 = Read_Heading(); //Return orientation toward X axis

        if (Margina2)
        {
                if (Input2 < 361 && Input2 > 270)
                        Input2 = -360 + Input2;
        }
        else
        {
                if (Input2 > -1 && Input2 < 90)
                        Input2 = 360 + Input2;
        }

        PID_Back.Compute();

        SetMotorSpeedAndDirection(SPEED_LEFT_MOTOR_PIN, DIRECTION_LEFT_MOTOR_PIN, motor_speed);
        SetMotorSpeedAndDirection(SPEED_RIGHT_MOTOR_PIN, DIRECTION_RIGHT_MOTOR_PIN, motor_speed);
        // Serial.println("Go_Back() function is called.");
}

void ROBOT_GIBANJE::Go_Right(int motor_speed)
{ // Default speed is maximum when you don't send any value to function

        SetMotorSpeedAndDirection(SPEED_LEFT_MOTOR_PIN, DIRECTION_LEFT_MOTOR_PIN, -motor_speed);
        SetMotorSpeedAndDirection(SPEED_RIGHT_MOTOR_PIN, DIRECTION_RIGHT_MOTOR_PIN, motor_speed);
        // Serial.println("Go_Left() function is called.");
}

void ROBOT_GIBANJE::Go_Left(int motor_speed)
{ // Default speed is maximum when you don't send any value to function

        SetMotorSpeedAndDirection(SPEED_LEFT_MOTOR_PIN, DIRECTION_LEFT_MOTOR_PIN, motor_speed);
        SetMotorSpeedAndDirection(SPEED_RIGHT_MOTOR_PIN, DIRECTION_RIGHT_MOTOR_PIN, -motor_speed);
        // Serial.println("Go_Right() function is called.");
}

void ROBOT_GIBANJE::Stop_Robot()
{

        SetMotorSpeedAndDirection(SPEED_LEFT_MOTOR_PIN, DIRECTION_LEFT_MOTOR_PIN, 0);
        SetMotorSpeedAndDirection(SPEED_RIGHT_MOTOR_PIN, DIRECTION_RIGHT_MOTOR_PIN, 0);
        // Serial.println("Stop_Robot() function is called.");
}

uint16_t ROBOT_GIBANJE::Read_Forward_Left_Distance()
{
        return lidar.distance(0);
}

uint16_t ROBOT_GIBANJE::Read_Forward_Middle_Distance()
{
        return lidar.distance(1);
}

uint16_t ROBOT_GIBANJE::Read_Forward_Right_Distance()
{
        return lidar.distance(2);
}

uint16_t ROBOT_GIBANJE::Read_Left_Back_Distance()
{
        return lidar.distance(3);
}

uint16_t ROBOT_GIBANJE::Read_Left_Front_Distance()
{
        return lidar.distance(4);
}

uint16_t ROBOT_GIBANJE::Read_Right_Back_Distance()
{
        return lidar.distance(5);
}

uint16_t ROBOT_GIBANJE::Read_Right_Front_Distance()
{
        return lidar.distance(6);
}

uint16_t ROBOT_GIBANJE::Read_Back_Left_Distance()
{
        return lidar.distance(7);
}

uint16_t ROBOT_GIBANJE::Read_Back_Middle_Distance()
{
        return lidar.distance(8);
}

uint16_t ROBOT_GIBANJE::Read_Back_Right_Distance()
{
        return lidar.distance(9);
}

void ROBOT_GIBANJE::Read_All_Distances()
{

        for (int i = 0; i < MAX_VL53L0XS_ANALOG; i++)
        {
                Distance_Array[i] = lidar.distance(i);
        }
}

void ROBOT_GIBANJE::Test_All_Distance_Sensors_One_By_One(int sensor_number)
{
        if (sensor_number == 0)
        {
                Serial.print("Prednji lijevi: ");
                Serial.println(Read_Forward_Left_Distance());
                delay(1000);
        }
        else if (sensor_number == 1)
        {
                Serial.print("Prednji srednji: ");
                Serial.println(Read_Forward_Middle_Distance());
                delay(1000);
        }
        else if (sensor_number == 2)
        {
                Serial.print("Prednji desni: ");
                Serial.println(Read_Forward_Right_Distance());
                delay(1000);
        }
        else if (sensor_number == 3)
        {
                Serial.print("Lijevi zadnji: ");
                Serial.println(Read_Left_Back_Distance());
                delay(1000);
        }
        else if (sensor_number == 4)
        {
                Serial.print("Lijevi prednji: ");
                Serial.println(Read_Left_Front_Distance());
                delay(1000);
        }
        else if (sensor_number == 5)
        {
                Serial.print("Desni zadnji: ");
                Serial.println(Read_Right_Back_Distance());
                delay(1000);
        }
        else if (sensor_number == 6)
        {
                Serial.print("Desni prednji: ");
                Serial.println(Read_Right_Front_Distance());
                delay(1000);
        }
        else if (sensor_number == 7)
        {
                Serial.print("Zadnji lijevi: ");
                Serial.println(Read_Back_Left_Distance());
                delay(1000);
        }
        else if (sensor_number == 8)
        {
                Serial.print("Zadnji srednji: ");
                Serial.println(Read_Back_Middle_Distance());
                delay(1000);
        }
        else if (sensor_number == 9)
        {
                Serial.print("Zadnji desni: ");
                Serial.println(Read_Back_Right_Distance());
                delay(1000);
        }
}

void ROBOT_GIBANJE::Go_Forward_30cm(int motor_speed)
{ // Default speed is maximum when you don't send any value to function

        uint16_t first_distance = Read_Forward_Middle_Distance();
        // Serial.println(first_distance);
        if (first_distance > 335)
        {
                uint16_t allowed_error = 0; // This number can be changed to achieve correct movement

                Setpoint1 = Read_Heading(); //Return orientation toward X axis

                if (Setpoint1 <= 180) // da li se nalazi u 1. i 4. kvadrantu ili 2. i 3. kvadrantu
                {
                        Margina1 = true;
                }
                else
                        Margina1 = false;

                while (Read_Forward_Middle_Distance() > (first_distance - 300 + allowed_error))
                { // -300 da ide za 30 cm unaprijed
                        Go_Forward(motor_speed);
                        // Serial.println(Read_Forward_Distance());
                }
                Stop_Robot();
                // Serial.println("Go_Forward_30cm() function is called.");
        }
}

void ROBOT_GIBANJE::Go_Back_30cm(int motor_speed)
{

        uint16_t first_distance = Read_Forward_Middle_Distance();

        // Serial.println(first_distance);
        uint16_t allowed_error = 0; // This number can be changed to achieve correct movement

        Setpoint2 = Read_Heading(); //Return orientation toward X axis

        if (Setpoint2 <= 180) // da li se nalazi u 1. i 4. kvadrantu ili 2. i 3. kvadrantu
        {
                Margina2 = true;
        }
        else
                Margina2 = false;

        while (Read_Forward_Middle_Distance() < (first_distance + 300 - allowed_error))
        {
                Go_Back(motor_speed);
                // Serial.println(Read_Forward_Distance());
        }
        Stop_Robot();
        // Serial.println("Go_Back_30cm() function is called.");
}

float ROBOT_GIBANJE::Read_Heading()
{ //Return orientation toward X axis

        sensors_event_t event;
        gyroscope.getEvent(&event);
        //Serial.println("Temporary robot orientation toward X axis is: ");
        //Serial.println(event.orientation.x);
        return event.orientation.x;
}

// When going right angle is increasing from 0 to 360
void ROBOT_GIBANJE::Go_Right_90degrees(int motor_speed)
{ // Default speed for turning right is 30, when you don't send any value to function

        uint16_t initial_heading = Read_Heading(); //Return orientation toward X axis
        uint8_t allowed_error = 5;                 // This number can be changed to achieve precise turns
        if (initial_heading < 270)
        {
                while (Read_Heading() < (initial_heading + 90 - allowed_error))
                {
                        Go_Right(motor_speed);
                }
        }
        else
        {
                while ((Read_Heading() <= 360) && (Read_Heading() >= 270))
                {
                        Go_Right(motor_speed);
                }
                while (Read_Heading() < (initial_heading - 270 - allowed_error))
                {
                        Go_Right(motor_speed);
                }
        }
        Stop_Robot();
        // Serial.println("Go_Right_90degrees() function is called.");
}

// When going left angle is decreasing from 360 to 0
void ROBOT_GIBANJE::Go_Left_90degrees(int motor_speed)
{ // Default speed for turning left is 30, when you don't send any value to function

        uint16_t initial_heading = Read_Heading();
        uint8_t allowed_error = 5; // This number can be changed to achieve precise turns
        if (initial_heading > 90)
        {
                while (Read_Heading() > (initial_heading - 90 + allowed_error))
                {
                        Go_Left(motor_speed);
                }
        }
        else
        {
                while ((Read_Heading() >= 0) && (Read_Heading() <= 90))
                {
                        Go_Left(motor_speed);
                }
                while (Read_Heading() > (initial_heading + 270 + allowed_error))
                {
                        Go_Left(motor_speed);
                }
        }
        Stop_Robot();
        // Serial.println("Go_Left_90degrees() function is called.");
}

void ROBOT_GIBANJE::Go_180degrees(int motor_speed)
{ // Default speed for turning is 30, when you don't send any value to function
        Go_Left_90degrees(motor_speed);
        Go_Left_90degrees(motor_speed);
}

uint16_t ROBOT_GIBANJE::Read_Temperature()
{
        return map(analogRead(THERMAL_OUT_PIN), 0, 52851, -20, 100);
}

bool ROBOT_GIBANJE::Is_Wall_Left()
{
        if ((Read_Left_Back_Distance() < Check_Walls_Distance) || (Read_Left_Front_Distance() < Check_Walls_Distance))
                return true;
        else
                return false;
}
bool ROBOT_GIBANJE::Is_Wall_Right()
{
        if ((Read_Right_Back_Distance() < Check_Walls_Distance) || (Read_Right_Front_Distance() < Check_Walls_Distance))
                return true;
        else
                return false;
}
bool ROBOT_GIBANJE::Is_Wall_Forward()
{
        if ((Read_Forward_Left_Distance() < Check_Walls_Distance) || (Read_Forward_Middle_Distance() < Check_Walls_Distance) || (Read_Forward_Right_Distance() < Check_Walls_Distance))
                return true;
        else
                return false;
}
bool ROBOT_GIBANJE::Is_Wall_Back()
{
        if ((Read_Back_Left_Distance() < Check_Walls_Distance) || (Read_Back_Middle_Distance() < Check_Walls_Distance) || (Read_Back_Right_Distance() < Check_Walls_Distance))
                return true;
        else
                return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool ROBOT_GIBANJE::Moveing_Is_Wall_Opend_Left()
{
        if ((Read_Left_Back_Distance() > Check_Walls_Distance) && (Read_Left_Front_Distance() > Check_Walls_Distance))
                return true;
        else
                return false;
}
bool ROBOT_GIBANJE::Moveing_Is_Wall_Opend_Right()
{
        if ((Read_Right_Back_Distance() > Check_Walls_Distance) && (Read_Right_Front_Distance() > Check_Walls_Distance))
                return true;
        else
                return false;
}
bool ROBOT_GIBANJE::Moveing_Is_Wall_Opend_Forward()
{
        if ((Read_Forward_Left_Distance() > Check_Walls_Distance) && (Read_Forward_Middle_Distance() > Check_Walls_Distance) && (Read_Forward_Right_Distance() > Check_Walls_Distance))
                return true;
        else
                return false;
}
bool ROBOT_GIBANJE::Moveing_Is_Wall_Opend_Back()
{
        if ((Read_Back_Left_Distance() > Check_Walls_Distance) && (Read_Back_Middle_Distance() > Check_Walls_Distance) && (Read_Back_Right_Distance() > Check_Walls_Distance))
                return true;
        else
                return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool ROBOT_GIBANJE::Moveing_Is_Wall_Left()
{
        if ((Read_Left_Back_Distance() < Stop_Distance) && (Read_Left_Front_Distance() < Stop_Distance))
                return true;
        else
                return false;
}
bool ROBOT_GIBANJE::Moveing_Is_Wall_Right()
{
        if ((Read_Right_Back_Distance() < Stop_Distance) && (Read_Right_Front_Distance() < Stop_Distance))
                return true;
        else
                return false;
}
bool ROBOT_GIBANJE::Moveing_Is_Wall_Forward()
{
        if ((Read_Forward_Left_Distance() < Stop_Distance) || (Read_Forward_Right_Distance() < Stop_Distance))
                return true;
        else
                return false;
}
bool ROBOT_GIBANJE::Moveing_Is_Wall_Back()
{
        if ((Read_Back_Left_Distance() < Stop_Distance) && (Read_Back_Right_Distance() < Stop_Distance))
                return true;
        else
                return false;
}

void ROBOT_GIBANJE::Push_Box()
{
        digitalWrite(ELECTROMAGNET_PIN1, LOW);
        digitalWrite(ELECTROMAGNET_PIN2, HIGH);
        delay(2000);
        digitalWrite(ELECTROMAGNET_PIN1, LOW);
        digitalWrite(ELECTROMAGNET_PIN2, LOW);
}

void error(String message)
{ // error message za VL53L0XsAnalog

        Serial.print(message);
        while (true)
                ;
}

void ROBOT_GIBANJE::Find_and_Align_Left_Wall()
{
        uint16_t Current_Left_Front_Distance = Read_Left_Front_Distance();
        uint16_t Current_Left_Back_Distance = Read_Left_Back_Distance();
        uint16_t Alowed_Error = 5; //This two sensors values need to be very closed because we want precise robot alignment toward left wall

        while (((Current_Left_Front_Distance - Current_Left_Back_Distance) > Alowed_Error) || ((Current_Left_Front_Distance - Current_Left_Back_Distance) < (-Alowed_Error)))
        {
                Go_Left();
                Current_Left_Front_Distance = Read_Left_Front_Distance();
                Current_Left_Back_Distance = Read_Left_Back_Distance();
                Serial.print("Front...");
                Serial.println(Current_Left_Front_Distance);
                Serial.print("Back...");
                Serial.println(Current_Left_Back_Distance);
                Serial.print("Razlika...");
                Serial.println(Current_Left_Front_Distance - Current_Left_Back_Distance);
                Serial.println("We are trying to allign robot left side...");
                delay(200);
        }
        Serial.println("Robot is alligned with left side.");
        Stop_Robot();
        //delay(200);

        //First break point

        /*
############################## PSEUDO CODE ############################## 
1.Rotate
2.When two left sensors have similar distances, stop rotating
#########################################################################
*/
}

void ROBOT_GIBANJE::Center_Robot()
{
        if ((Moveing_Is_Wall_Forward() && Moveing_Is_Wall_Left()) || (Moveing_Is_Wall_Forward() && Moveing_Is_Wall_Right()))
                Serial.println("Robot front side is oriented toward closed  maze side.");

        else if ((Moveing_Is_Wall_Back() && Moveing_Is_Wall_Left()) || (Moveing_Is_Wall_Back() && Moveing_Is_Wall_Right()))
        {
                Go_180degrees();
                Serial.println("Rotating left for 180 degrees...Robot front side is oriented toward closed  maze side.");
        }

        else if ((Moveing_Is_Wall_Left() && Moveing_Is_Wall_Forward()) || (Moveing_Is_Wall_Left() || Moveing_Is_Wall_Back()))
        {
                Go_Left_90degrees();
                Serial.println("Rotating left for 90 degrees...Robot front side is oriented toward closed  maze side.");
        }

        else if ((Moveing_Is_Wall_Right() && Moveing_Is_Wall_Forward()) || (Moveing_Is_Wall_Right() || Moveing_Is_Wall_Back()))
        {
                Go_Right_90degrees();
                Serial.println("Rotating right for 90 degrees...Robot front side is oriented toward closed  maze side.");
        }
        //else Serial.println("Maybe make function for rotation of 45 degrees is else case!?");DrzacZaBateriju
        //Second break point

        if ((Read_Forward_Left_Distance() < (Stop_Distance_For_Center_Robot)) && (Read_Forward_Right_Distance() < (Stop_Distance_For_Center_Robot)))
        {
                while ((Read_Forward_Left_Distance() < (Stop_Distance_For_Center_Robot)) && (Read_Forward_Right_Distance() < (Stop_Distance_For_Center_Robot)))
                {
                        Go_Back();
                        Read_Forward_Left_Distance();
                        Read_Forward_Right_Distance();
                }
        }

        else if ((Read_Forward_Left_Distance() > (Stop_Distance_For_Center_Robot)) && (Read_Forward_Right_Distance() > (Stop_Distance_For_Center_Robot)))
        {
                while ((Read_Forward_Left_Distance() > (Stop_Distance_For_Center_Robot)) && (Read_Forward_Right_Distance() > (Stop_Distance_For_Center_Robot)))
                {
                        Go_Forward();
                        Read_Forward_Left_Distance();
                        Read_Forward_Right_Distance();
                }
        }

        if (Moveing_Is_Wall_Left())
        {
                Go_Left_90degrees();
        }

        else if (Moveing_Is_Wall_Right())
        {
                Go_Right_90degrees();
        }

        if ((Read_Forward_Left_Distance() < (Stop_Distance_For_Center_Robot)) && (Read_Forward_Right_Distance() < (Stop_Distance_For_Center_Robot)))
        {
                while ((Read_Forward_Left_Distance() < (Stop_Distance_For_Center_Robot)) && (Read_Forward_Right_Distance() < (Stop_Distance_For_Center_Robot)))
                {
                        Go_Back();
                        Read_Forward_Left_Distance();
                        Read_Forward_Right_Distance();
                }
        }

        else if ((Read_Forward_Left_Distance() > (Stop_Distance_For_Center_Robot)) && (Read_Forward_Right_Distance() > (Stop_Distance_For_Center_Robot)))
        {
                while ((Read_Forward_Left_Distance() > (Stop_Distance_For_Center_Robot)) && (Read_Forward_Right_Distance() > (Stop_Distance_For_Center_Robot)))
                {
                        Go_Forward();
                        Read_Forward_Left_Distance();
                        Read_Forward_Right_Distance();
                }
        }

        /*
############################## PSEUDO CODE ############################## 
1.Rotate front robot side toward closed wall on which are attached one more wall (left or right one)
2.Go forward or backward and stop when needed distance is found
3.Rotate front robot side for +-90 degrees oriented toward wall founded in first step (finding left or right wall)
4.Go forward or backward and stop when needed distance is found
5.Robot is centered
#########################################################################
*/
}

void ROBOT_GIBANJE::Find_and_Rotate_To_Opend_Wall()
{
        /*
if (( Read_Forward_Left_Distance() && Read_Forward_Middle_Distance() && Read_Forward_Right_Distance()) > Check_Walls_Distance) Serial.println("Robot front side is oriented toward opened  maze side.");

else if((Read_Back_Left_Distance() && Read_Back_Middle_Distance() && Read_Back_Right_Distance()) > Check_Walls_Distance ){
        Go_180degrees();
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

        if (Moveing_Is_Wall_Opend_Forward())
                Serial.println("Robot front side is oriented toward opened  maze side.");

        else if (Moveing_Is_Wall_Opend_Back())
        {
                Go_180degrees();
                Serial.println("Rotating left for 180 degrees...Robot front side is oriented toward opened  maze side.");
        }

        else if (Moveing_Is_Wall_Opend_Left())
        {
                Go_Left_90degrees();
                Serial.println("Rotating left for 90 degrees...Robot front side is oriented toward opened  maze side.");
        }

        else if (Moveing_Is_Wall_Opend_Right())
        {
                Go_Right_90degrees();
                Serial.println("Rotating right for 90 degrees...Robot front side is oriented toward opened  maze side.");
        }

        else
                Serial.println("Maybe make function for rotation of 45 degrees in else case!?");

        //Seconde break point

        /*
############################## PSEUDO CODE ############################## 
1.Robot stays od the place and try to find opend maze side with distance sensor
2.Rotate robot toward opend side
#########################################################################
*/
}

void ROBOT_GIBANJE::Automomus_Maze_Path_Finding()
{

        if ((Read_Forward_Left_Distance() > 300) && (Read_Forward_Right_Distance() > 300))
        {
                Go_Forward_30cm();
                Serial.println("Going forward to the first wall.");
                Serial.print("Autonomus mode-Forward Left Distance:");
                Serial.println(Read_Forward_Left_Distance());
                Serial.print("Autonomus mode-Forward Right Distance:");
                Serial.println(Read_Forward_Right_Distance());
        }

        else if ((Read_Forward_Left_Distance() < 300) && (Read_Forward_Right_Distance() < 300))
        {
                Go_Forward();
                Serial.println("Going forward to the first wall.");
                Serial.print("Autonomus mode-Forward Left Distance:");
                Serial.println(Read_Forward_Left_Distance());
                Serial.print("Autonomus mode-Forward Right Distance:");
                Serial.println(Read_Forward_Right_Distance());
                if (Moveing_Is_Wall_Forward())
                {
                        Stop_Robot();
                        Find_and_Rotate_To_Opend_Wall();
                }
        }

        else
        {
                Go_Forward();
                Serial.println("Going forward to the first wall.");
                Serial.print("Autonomus mode-Forward Left Distance:");
                Serial.println(Read_Forward_Left_Distance());
                Serial.print("Autonomus mode-Forward Right Distance:");
                Serial.println(Read_Forward_Right_Distance());
                if (Moveing_Is_Wall_Forward())
                {
                        Stop_Robot();
                        Find_and_Rotate_To_Opend_Wall();
                }
        }

        /*
############################## PSEUDO CODE ############################## 
1.Robot goes forward with 30cm if the next wall is away
2.When the wall is near to robot we go forward with smaller step than is 30cm
3.When wall is too close to front robot side we stop robot
4.Finding and rotation robot toward current opend wall  
#########################################################################
*/
}

void ROBOT_GIBANJE::Rotate_Right_With_Specific_Angle(int angle, int delayTime = 0, int motor_speed = 30) //angle ust be  values between 0 and 90 degrees
{
  int current_Orientation=Read_Heading();
        int16_t wanted_heading;
        Serial.print("Current Orientation: ");
        Serial.println(current_Orientation);
        delay(delayTime);

        if ((current_Orientation >= 271) && (current_Orientation <= 360))
        {
                current_Orientation = current_Orientation - 360;
                wanted_heading = current_Orientation + angle;

                if (wanted_heading > 360)
                {
                        wanted_heading = wanted_heading - 360;
                }

                Serial.println("I am in If loop.");

                Serial.print("Current Orientation: ");
                Serial.println(current_Orientation);

                Serial.print("Wanted heading: ");
                Serial.println(wanted_heading);

                delay(delayTime);

                while ((current_Orientation >= -89) && (current_Orientation < 0) && (current_Orientation < wanted_heading))
                {

                        Serial.println("I am in 1 If While loop.");

                        Serial.print("Current Orientation: ");
                        Serial.println(current_Orientation);

                        Serial.print("Wanted heading: ");
                        Serial.println(wanted_heading);
                        delay(delayTime);

                        Go_Right();

                        current_Orientation = Read_Heading() - 360;
                        Serial.println("Robot rotated.");
                        Serial.println(current_Orientation);
                }

                current_Orientation = Read_Heading();

                while (current_Orientation < wanted_heading)
                {
                        Serial.println("I am in 2 If While loop.");

                        Serial.print("Current Orientation: ");
                        Serial.println(current_Orientation);

                        Serial.print("Wanted heading: ");
                        Serial.println(wanted_heading);
                        delay(delayTime);

                        Go_Right();
                        current_Orientation = Read_Heading();
                        Serial.println("Robot rotated.");
                        Serial.println(current_Orientation);
                }
        }

        else
        {
                current_Orientation = current_Orientation;
                wanted_heading = current_Orientation + angle;

                if (wanted_heading > 360)
                {
                        wanted_heading = wanted_heading - 360;
                }

                Serial.println("I am in Else loop.");

                Serial.print("Current Orientation: ");
                Serial.println(current_Orientation);

                Serial.print("Wanted heading: ");
                Serial.println(wanted_heading);

                delay(delayTime);

                while (current_Orientation < wanted_heading)
                {
                        Serial.println("I am in Else While loop.");

                        Serial.print("Current Orientation: ");
                        Serial.println(current_Orientation);

                        Serial.print("Wanted heading: ");
                        Serial.println(wanted_heading);

                        delay(delayTime);

                        Go_Right();
                        current_Orientation = Read_Heading();
                        Serial.println("Robot rotated.");
                        Serial.println(current_Orientation);
                }
        }

        Stop_Robot();
        delay(delayTime); //################################################################################
        Serial.println("Robot rotated END.");
        Serial.println(current_Orientation);
}

void ROBOT_GIBANJE::Rotate_Left_With_Specific_Angle(int angle, int delayTime = 0, int motor_speed = 30) //angle ust be  values between 0 and 90 degrees
{
        
        int current_Orientation=Read_Heading();

        int16_t wanted_heading;
        Serial.print("Current Orientation: ");
        Serial.println(current_Orientation);
        delay(delayTime);

        if ((current_Orientation >= 0) && (current_Orientation <= 89))
        {
                current_Orientation = current_Orientation + 360;
                wanted_heading = current_Orientation - angle;

                if (wanted_heading < 0)
                {
                        wanted_heading = wanted_heading + 360;
                }

                Serial.println("I am in If loop.");

                Serial.print("Current Orientation: ");
                Serial.println(current_Orientation);

                Serial.print("Wanted heading: ");
                Serial.println(wanted_heading);
                delay(delayTime);

                while ((current_Orientation >= 360) && (current_Orientation < 449) && (current_Orientation > wanted_heading))
                {

                        Serial.println("I am in 1 If While loop.");

                        Serial.print("Current Orientation: ");
                        Serial.println(current_Orientation);

                        Serial.print("Wanted heading: ");
                        Serial.println(wanted_heading);
                        delay(delayTime);

                        Go_Left();

                        current_Orientation = Read_Heading() + 360;
                        Serial.println("Robot rotated.");
                        Serial.println(current_Orientation);
                }

                current_Orientation = Read_Heading();

                while (current_Orientation > wanted_heading)
                {
                        Serial.println("I am in 2 If While loop.");

                        Serial.print("Current Orientation: ");
                        Serial.println(current_Orientation);

                        Serial.print("Wanted heading: ");
                        Serial.println(wanted_heading);
                        delay(delayTime);

                        Go_Left();
                        current_Orientation = Read_Heading();
                        Serial.println("Robot rotated.");
                        Serial.println(current_Orientation);
                }
        }

        else
        {
                current_Orientation = current_Orientation;
                wanted_heading = current_Orientation - angle;

                if (wanted_heading < 0)
                {
                        wanted_heading = wanted_heading + 360;
                }

                Serial.println("I am in Else loop.");

                Serial.print("Current Orientation: ");
                Serial.println(current_Orientation);

                Serial.print("Wanted heading: ");
                Serial.println(wanted_heading);
                delay(delayTime);

                while (current_Orientation > wanted_heading)
                {
                        Serial.println("I am in Else While loop.");

                        Serial.print("Current Orientation: ");
                        Serial.println(current_Orientation);

                        Serial.print("Wanted heading: ");
                        Serial.println(wanted_heading);
                        delay(delayTime);

                        Go_Left();
                        current_Orientation = Read_Heading();
                        Serial.println("Robot rotated.");
                        Serial.println(current_Orientation);
                }
        }

        Stop_Robot();
        delay(delayTime); //################################################################################
        Serial.println("Robot rotated END.");
        Serial.println(current_Orientation);
}

int ROBOT_GIBANJE::Align_To_Left_Wall(int Alowed_Error = 1, int delayTime = 0)
{
        float WallFollowingError = Read_Left_Front_Distance() - Read_Left_Back_Distance();

        Serial.println("No Loop");
        Serial.print("Prednji lijevi senzor: ");
        Serial.println(Read_Left_Front_Distance());

        Serial.print("Zadnji lijevi senzor: ");
        Serial.println(Read_Left_Back_Distance());

        Serial.print("Pogreška praćanja zida: ");
        Serial.println(WallFollowingError);
        Serial.println(" ");

        delay(delayTime);

        if (((WallFollowingError * WallFollowingError) > Alowed_Error * Alowed_Error))
        {

                Serial.println("I am in Error While loop.");
                Serial.println(" ");
                delay(delayTime);

                while (WallFollowingError > Alowed_Error)
                {
                        Go_Left();
                        WallFollowingError = Read_Left_Front_Distance() - Read_Left_Back_Distance();
                        Serial.print("Error: ");
                        Serial.println(WallFollowingError);
                        Serial.println("Going Right.");
                        Serial.println("Robot aligned in 1st While Loop.");
                }

                while (WallFollowingError < -Alowed_Error)
                {
                        Go_Right();
                        WallFollowingError = Read_Left_Front_Distance() - Read_Left_Back_Distance();
                        Serial.print("Error: ");
                        Serial.println(WallFollowingError);
                        Serial.println("Going Left.");
                        Serial.println("Robot aligned in 2nd While Loop.");
                }

                Stop_Robot();
                //delay(100); //#############################################################################################################
                Serial.println(" ");
        }

        int16_t initial_heading = Read_Heading();
        return initial_heading;
}

int ROBOT_GIBANJE::Front_Stop_Distance(float Maze_Plate_Lenght = 325, float Snesor_Distance_From_Robot_Center_Point = 67.167)
{
        float Stop_Distance_For_Center_Robot = (Maze_Plate_Lenght / 2) - Snesor_Distance_From_Robot_Center_Point;
        return Stop_Distance_For_Center_Robot;
}

void ROBOT_GIBANJE::Follow_Gyrosope_With_PID_Controller(int Orientation_Tolerance = 1,int delayTime = 0, int LeftandRightSpeed = 20)
{
        int Current_Orientation;
        
        Setpoint1 = Read_Heading();

        Serial.println("Decided orientation: ");
        Serial.println(Setpoint1);
        Serial.println("#################################################");
        Serial.println(" ");

        int Fordward_Left = Read_Forward_Left_Distance();   // Senzori prednja strana
        int Fordward_Right = Read_Forward_Right_Distance(); // Senzori prednja strana

        int Critical_Left = Read_Left_Front_Distance();   //Snezor lijeva strana
        int Critical_Right = Read_Right_Front_Distance(); //Snezor desna strana

        delay(delayTime);

        while ((Fordward_Left > Front_Stop_Distance_Check) && (Fordward_Right > Front_Stop_Distance_Check))
        {

                while ((Critical_Left > 100) && (Critical_Right > 100))
                {

                        Current_Orientation = int(Read_Heading());
                        Serial.println(" ");
                        Serial.println("I 'am in first while loop.");
                        Serial.println("Current orientation 1st time: ");
                        Serial.println(Current_Orientation);
                        Serial.println(" ");
                        delay(delayTime);

                        if ((Setpoint1 >= 0) && (Setpoint1 <= 89))
                        {
                                int Setpoint1_Temp = Setpoint1 + 360;

                                if ((Current_Orientation >= 0) && (Current_Orientation <= 89))
                                {

                                        Current_Orientation = Current_Orientation + 360;
                                }
                                else
                                {
                                        Current_Orientation = Current_Orientation;
                                }

                                Serial.println("Current orientation in IF condition: ");
                                Serial.println(Current_Orientation);
                                Serial.println("Decided orientation in IF condition: ");
                                Serial.println(Setpoint1_Temp);
                                Serial.println(" ");
                                delay(delayTime);

                                while ((Current_Orientation - Setpoint1_Temp) > Orientation_Tolerance)
                                {
                                        Go_Left(LeftandRightSpeed);

                                        Current_Orientation = int(Read_Heading());

                                        if ((Current_Orientation >= 0) && (Current_Orientation <= 89))
                                        {

                                                Current_Orientation = Current_Orientation + 360;
                                        }
                                        else
                                        {
                                                Current_Orientation = Current_Orientation;
                                        }

                                        Serial.println("Current orientation in IF 1st WHILE LOOP: ");
                                        Serial.println(Current_Orientation);
                                        Serial.println("Decided orientation in IF 1st WHILE LOOP: ");
                                        Serial.println(Setpoint1_Temp);
                                        Serial.println("Current EROR in IF 1st WHILE LOOP: ");
                                        Serial.println(Current_Orientation - Setpoint1_Temp);
                                        Serial.println(" ");
                                        delay(delayTime);
                                }

                                Go_Forward();
                                Serial.println("Fobot follow gyroscope.");
                                Serial.println(" ");

                                Fordward_Left = Read_Forward_Left_Distance();   // Senzori prednja strana
                                Fordward_Right = Read_Forward_Right_Distance(); // Senzori prednja strana
                                Critical_Left = Read_Left_Front_Distance();     //Snezor lijeva strana
                                Critical_Right = Read_Right_Front_Distance();   //Snezor desna strana

                                while ((Current_Orientation - Setpoint1_Temp) < -Orientation_Tolerance)
                                {
                                        Go_Right(LeftandRightSpeed);

                                        Current_Orientation = int(Read_Heading());

                                        if ((Current_Orientation >= 0) && (Current_Orientation <= 89))
                                        {

                                                Current_Orientation = Current_Orientation + 360;
                                        }
                                        else
                                        {
                                                Current_Orientation = Current_Orientation;
                                        }

                                        Serial.println("Current orientation in IF 2nd WHILE LOOP: ");
                                        Serial.println(Current_Orientation);
                                        Serial.println("Decided orientation in IF 2nd WHILE LOOP: ");
                                        Serial.println(Setpoint1_Temp);
                                        Serial.println("Current EROR in IF 2nd WHILE LOOP: ");
                                        Serial.println(Current_Orientation - Setpoint1_Temp);
                                        Serial.println(" ");
                                        delay(delayTime);
                                }

                                Go_Forward();
                                Serial.println("Fobot follow gyroscope.");
                                Serial.println(" ");

                                Fordward_Left = Read_Forward_Left_Distance();   // Senzori prednja strana
                                Fordward_Right = Read_Forward_Right_Distance(); // Senzori prednja strana
                                Critical_Left = Read_Left_Front_Distance();     //Snezor lijeva strana
                                Critical_Right = Read_Right_Front_Distance();   //Snezor desna strana
                        }

                        else if ((Setpoint1 >= 271) && (Setpoint1 <= 360))
                        {
                                int Setpoint1_Temp = Setpoint1 - 360;
                                Current_Orientation = int(Read_Heading());

                                if ((Current_Orientation >= 271) && (Current_Orientation <= 360))
                                {

                                        Current_Orientation = Current_Orientation - 360;
                                }
                                else
                                {

                                        Current_Orientation = Current_Orientation;
                                }

                                Serial.println("Current orientation in ELSE IF condition: ");
                                Serial.println(Current_Orientation);
                                Serial.println("Decided orientation in ELSE IF condition: ");
                                Serial.println(Setpoint1_Temp);
                                Serial.println(" ");
                                delay(delayTime);

                                while ((Current_Orientation - Setpoint1_Temp) > Orientation_Tolerance)
                                {
                                        Go_Left(LeftandRightSpeed);
                                        Current_Orientation = int(Read_Heading());

                                        if ((Current_Orientation >= 271) && (Current_Orientation <= 360))
                                        {

                                                Current_Orientation = Current_Orientation - 360;
                                        }
                                        else
                                        {
                                                Current_Orientation = Current_Orientation;
                                        }

                                        Serial.println("Current orientation in ELSE IF 1st WHILE LOOP: ");
                                        Serial.println(Current_Orientation);
                                        Serial.println("Decided orientation in ELSE IF 1st WHILE LOOP: ");
                                        Serial.println(Setpoint1_Temp);
                                        Serial.println("Current EROR in ELSE IF 1st WHILE LOOP: ");
                                        Serial.println(Current_Orientation - Setpoint1_Temp);
                                        Serial.println(" ");
                                        delay(delayTime);
                                }

                                Go_Forward();
                                Serial.println("Fobot follow gyroscope.");
                                Serial.println(" ");

                                Fordward_Left = Read_Forward_Left_Distance();   // Senzori prednja strana
                                Fordward_Right = Read_Forward_Right_Distance(); // Senzori prednja strana
                                Critical_Left = Read_Left_Front_Distance();     //Snezor lijeva strana
                                Critical_Right = Read_Right_Front_Distance();   //Snezor desna strana

                                while ((Current_Orientation - Setpoint1_Temp) < -Orientation_Tolerance)
                                {
                                        Go_Right(LeftandRightSpeed);
                                        Current_Orientation = int(Read_Heading());

                                        if ((Current_Orientation >= 271) && (Current_Orientation <= 360))
                                        {

                                                Current_Orientation = Current_Orientation - 360;
                                        }
                                        else
                                        {
                                                Current_Orientation = Current_Orientation;
                                        }

                                        Serial.println("Current orientation in ELSE IF 2nd WHILE LOOP: ");
                                        Serial.println(Current_Orientation);
                                        Serial.println("Decided orientation in ELSE IF 2nd WHILE LOOP: ");
                                        Serial.println(Setpoint1_Temp);
                                        Serial.println("Current EROR in ELSE IF 2nd WHILE LOOP: ");
                                        Serial.println(Current_Orientation - Setpoint1_Temp);
                                        Serial.println(" ");
                                        delay(delayTime);
                                }

                                Go_Forward();
                                Serial.println("Fobot follow gyroscope.");
                                Serial.println(" ");

                                Fordward_Left = Read_Forward_Left_Distance();   // Senzori prednja strana
                                Fordward_Right = Read_Forward_Right_Distance(); // Senzori prednja strana
                                Critical_Left = Read_Left_Front_Distance();     //Snezor lijeva strana
                                Critical_Right = Read_Right_Front_Distance();   //Snezor desna strana
                        }

                        else
                        {
                                while ((Current_Orientation - Setpoint1) > Orientation_Tolerance)
                                {
                                        Go_Left(LeftandRightSpeed);

                                        Current_Orientation = int(Read_Heading());

                                        Serial.println("Current orientation in ELSE 1st WHILE LOOP: ");
                                        Serial.println(Current_Orientation);
                                        Serial.println("Decided orientation in ELSE 1st WHILE LOOP: ");
                                        Serial.println(Setpoint1);
                                        Serial.println("Current EROR in ELSE 1st WHILE LOOP: ");
                                        Serial.println(Current_Orientation - Setpoint1);
                                        Serial.println(" ");
                                        delay(delayTime);
                                }

                                Go_Forward();
                                Serial.println("Fobot follow gyroscope.");
                                Serial.println(" ");
                                delay(500);
                                Stop_Robot();

                                Fordward_Left = Read_Forward_Left_Distance();   // Senzori prednja strana
                                Fordward_Right = Read_Forward_Right_Distance(); // Senzori prednja strana
                                Critical_Left = Read_Left_Front_Distance();     //Snezor lijeva strana
                                Critical_Right = Read_Right_Front_Distance();   //Snezor desna strana

                                while ((Current_Orientation - Setpoint1) < -Orientation_Tolerance)
                                {
                                        Go_Right(LeftandRightSpeed);

                                        Current_Orientation = int(Read_Heading());

                                        Serial.println("Current orientation in ELSE 2nd WHILE LOOP: ");
                                        Serial.println(Current_Orientation);
                                        Serial.println("Decided orientation in ELSE 2nd WHILE LOOP: ");
                                        Serial.println(Setpoint1);
                                        Serial.println("Current EROR in ELSE 2nd WHILE LOOP: ");
                                        Serial.println(Current_Orientation - Setpoint1);
                                        Serial.println(" ");
                                        delay(delayTime);
                                }

                                Go_Forward();
                                Serial.println("Fobot follow gyroscope.");
                                Serial.println(" ");
                                delay(500);
                                Stop_Robot();

                                Fordward_Left = Read_Forward_Left_Distance();   // Senzori prednja strana
                                Fordward_Right = Read_Forward_Right_Distance(); // Senzori prednja strana
                                Critical_Left = Read_Left_Front_Distance();     //Snezor lijeva strana
                                Critical_Right = Read_Right_Front_Distance();   //Snezor desna strana
                        }
                }

                if ((Critical_Left < 100))
                {
                        Rotate_Right_With_Specific_Angle(5);
                }
                else if ((Critical_Right < 100))
                {
                        Rotate_Left_With_Specific_Angle(5);
                }

                Fordward_Left = Read_Forward_Left_Distance();   // Senzori prednja strana
                Fordward_Right = Read_Forward_Right_Distance(); // Senzori prednja strana

                Critical_Left = Read_Left_Front_Distance();   //Snezor lijeva strana
                Critical_Right = Read_Right_Front_Distance(); //Snezor desna strana
        }

        Serial.println(" ");
        Serial.println("I am OUT MAIN WHILE LOOP");
        Serial.println(" ");

        Stop_Robot();

        Current_Orientation = Read_Heading();

        Fordward_Left = Read_Forward_Left_Distance();   // Senzori prednja strana
        Fordward_Right = Read_Forward_Right_Distance(); // Senzori prednja strana
}