// added encoder with interrupts
// added temperature sensor

#include "Robot_Gibanje.h"

ROBOT_GIBANJE robot;

//1525 encoder readings is 360 degrees whell rotation actually 157.1 mm
// 50 mm makes with 485 impulses

//Maximal speed is 100

// Z orientation Tolerance = 13

//Left front distance sensor measure bigger values

void setup()
{

  Serial.begin(115200); // Start communication with a computer connected to Teensy via a USB cable
  robot.SetupZaSveKomponente();
  delay(1000);
}

void loop()
{

  // Read the position in an atomic block to avoid a potential
  // misread if the interrupt coincides with this code running
  // see: https://www.arduino.cc/reference/en/language/variables/variable-scope-qualifiers/volatile/

  //Ocitanje texa koji dolazi na Arduino serijski port

  //robot.Read_Temperature_Left_Sensor();

  //####################################################################################################
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
  /*
*/
  //####################################################################################################
}

//Serial.println(i);

/*

  int Left_Front_Distance = robot.Read_Left_Front_Distance();
  int Left_Back_Distance = robot.Read_Left_Back_Distance();

  int Right_Front_Distance =robot. Read_Right_Front_Distance();
  int Right_Back_Distance = robot.Read_Right_Back_Distance();

  while ((Left_Front_Distance < 200) && (Left_Back_Distance < 200))
  {
    Serial.println(" ");
    Serial.println("GO RIGHT - Too closed to left wall.");
    Serial.println(" ");
    robot.Go_Forward(35, 10);
    delay(100);
    Left_Front_Distance = robot.Read_Left_Front_Distance();
    Left_Back_Distance = robot.Read_Left_Back_Distance();
  }
  robot.Go_Forward();
*/
//robot.Find_and_Rotate_To_Opend_Wall();
/*
Serial.print(robot.Read_Left_Front_Distance());
Serial.print("  ");
Serial.print(robot.Read_Left_Back_Distance());
Serial.print(" : ");
Serial.print(robot.Read_Right_Front_Distance());
Serial.print("  ");
Serial.println(robot.Read_Right_Back_Distance());
delay(1000);
*/

//Serial.println(robot.Read_Heading());

/*
  Serial.print(robot.Read_Left_Front_Distance());
Serial.print("  ");
Serial.print(robot.Read_Left_Back_Distance());
Serial.print(" : ");
Serial.print(robot.Read_Right_Front_Distance());
Serial.print("  ");
Serial.println(robot.Read_Right_Back_Distance());
delay(1000);

*/

/*
//Right front
Serial.print(robot.Read_Forward_Left_Distance());
Serial.print("  ");
//Left front
Serial.println(robot.Read_Forward_Right_Distance());
delay(1000);
*/

//robot.Search_for_Black_or_Grey_tiles();

//robot.Go_Forward();
//robot.Search_for_Black_or_Grey_tiles();

//Ocitanje texa koji dolazi na Arduino serijski port
/* if (Serial.available() > 0) {
    
  String data = Serial.readStringUntil('\n');
  
  if (data.substring(0) == "SFND") {
    Serial.println("FOUND");
    robot.Stop_Robot();
    delay(3000);

    }


  }
*/
