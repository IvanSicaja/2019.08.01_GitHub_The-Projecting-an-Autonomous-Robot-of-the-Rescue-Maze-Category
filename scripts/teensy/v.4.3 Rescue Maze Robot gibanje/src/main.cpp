
#include "Robot_Gibanje.h"

ROBOT_GIBANJE robot;

int The_Last_state_left_encoder;

void setup()
{
  Serial.begin(115200); // Start communication with a computer connected to Teensy via a USB cable
  robot.SetupZaSveKomponente();
  delay(1000);


}

// Loop function
void loop()
{

  robot.Read_Left_Encoder();
  /*
//Right Back
Serial.print(robot.Read_Left_Front_Distance());
Serial.print("  ");
Serial.println(robot.Read_Left_Back_Distance());
delay(1000);
*/

  /*
//Front Left
Serial.print(robot.Read_Right_Front_Distance());
Serial.print("  ");
//Front Right
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
