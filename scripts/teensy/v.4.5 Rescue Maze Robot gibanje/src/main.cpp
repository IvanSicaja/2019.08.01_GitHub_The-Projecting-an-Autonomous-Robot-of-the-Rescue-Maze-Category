
#include "Robot_Gibanje.h"

ROBOT_GIBANJE robot;

//1525 encoder readings is 360 degrees whell rotation actually 157.1 mm
// 50 mm makes with 485 impulses

//Maximal speed is 100

int The_Last_state_left_encoder;
int Setpoint_Orientation;

void setup()
{
  Serial.begin(115200); // Start communication with a computer connected to Teensy via a USB cable
  robot.SetupZaSveKomponente();
  Setpoint_Orientation = robot.Read_Heading();
  delay(1000);
}

// Loop function
void loop()
{
//robot.Go_Autonomus_with_PID();
  
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
}

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
