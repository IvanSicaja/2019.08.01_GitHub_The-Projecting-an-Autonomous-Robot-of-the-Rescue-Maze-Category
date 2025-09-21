
#include "Robot_Gibanje.h"

ROBOT_GIBANJE robot;

void setup()
{
      Serial.begin(115200); // Start communication with a computer connected to Teensy via a USB cable
      robot.SetupZaSveKomponente();
      delay(1000);
}

// Loop function
void loop()
{


int a=robot.Read_Forward_Left_Distance();
Serial.println(a);
delay(1000);
//robot.Go_Forward(30,30);
//delay(200);
//robot.Push_Box();
//delay(200);

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
 
