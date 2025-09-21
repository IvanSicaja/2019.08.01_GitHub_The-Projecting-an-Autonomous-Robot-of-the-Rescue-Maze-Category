// Regulators calibrated
// Added condition to giroscope while loop
// Added forward distance sensors value for else if conditions on main loop
// Added else condition
// Added or logic for condition of p-regulators loop
// Added Keep optimal distances to autonomus function
// Added time interval to giroscope and keep optimal distances regulators
// Adding boolean condition for turn-on and turn-off refulators of main loop

// added temperature sensor -> needs calibration
// added encoder with interrupts
// 1525 encoder readings is 360 degrees whell rotation actually 157.1 mm
// 50 mm makes with 485 impulses
// Maximal motor speed is 100
// Z orientation Tolerance = 13
// 17 is minimum speed of one wheel if one wheel speed is higer of 19


#include "Robot_Gibanje.h"

ROBOT_GIBANJE robot;

void setup()
{


  Serial.begin(115200); // Start communication with a computer connected to Teensy via a USB cable
  Serial.println("I am in setup loop.");
  robot.Setup_For_All_Components();   

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

robot.Go_Autonomus_Adventage_Version_Optimized();






  }



