
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
 
 
 robot.Follow_Gyrosope_With_PID_Controller(0,10);


}
