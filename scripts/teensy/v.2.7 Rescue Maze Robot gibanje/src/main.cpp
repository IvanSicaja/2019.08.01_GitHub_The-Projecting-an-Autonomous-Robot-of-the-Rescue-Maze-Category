
#include "Robot_Gibanje.h"

ROBOT_GIBANJE robot;


void setup() {



        Serial.begin(115200); // Start communication with a computer connected to Teensy via a USB cable

        robot.SetupZaSveKomponente();

        delay(1000);

}



// Loop function
void loop() {
 
//robot.Test_All_Distance_Sensors_One_By_One(3);

//Serial.println(robot.Read_Temperature());
//delay(1000);

//Serial.print("Temporary robot orientation toward X axis is: ");
//Serial.println(robot.Read_Heading());
//delay(300);

robot.Go_Left();
        
}
