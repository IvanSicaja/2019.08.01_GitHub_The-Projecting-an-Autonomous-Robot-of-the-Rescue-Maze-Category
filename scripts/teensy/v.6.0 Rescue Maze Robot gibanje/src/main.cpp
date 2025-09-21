//Reguletors calibrated
// Adding condition to giroscope while loop

// added temperature sensor -> needs calibration
// added encoder with interrupts
// 1525 encoder readings is 360 degrees whell rotation actually 157.1 mm
// 50 mm makes with 485 impulses
// Maximal motor speed is 100
// Z orientation Tolerance = 13
// 17 is minimum speed of one wheel if one wheel speed is higer of 19


#include "Robot_Gibanje.h"

ROBOT_GIBANJE robot;

int orientation;
int motor_speed;


void setup()
{

  Serial.begin(115200); // Start communication with a computer connected to Teensy via a USB cable
  robot.Setup_For_All_Components();

  motor_speed=20;
   

  delay(1000);
}

void loop()
{

  //####################################################################################################
  /*
  bool ArduinoStartsCommunication = false;

  while (ArduinoStartsCommunication != true)
  {
    if (Serial.available() > 0)
    {

      String data = Serial.readStringUntil('\n');

      if (data.substring(0) == "START!")
      {
        ArduinoStartsCommunication = true;
        Serial.println("START!");
      }
    }
  }

  robot.Go_Autonomus_with_PID();
*/


//robot.Read_All_Distances();

//robot.Stay_Away_From_Left_Wall();
//robot.Stay_Away_From_Right_Wall();
//robot.Keep_Optimal_Distance_With_Left_Wall();
//robot.Keep_Optimal_Distance_With_Right_Wall();

//robot.Go_Autonomus_Adventage_Version_Optimized();

motor_speed= robot.Optimize_speed_with_Z_Orientation_Optimized_For_Autonomus_Loop(20,8,15);
robot.Go_Forward(motor_speed,motor_speed);
delay(100);



  }



