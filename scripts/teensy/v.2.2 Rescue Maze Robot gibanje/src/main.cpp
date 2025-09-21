
#include "Robot_Gibanje.h"

ROBOT_GIBANJE robot;


void setup() {



        Serial.begin(115200); // Start communication with a computer connected to Teensy via a USB cable

        robot.SetupZaSveKomponente();

        delay(1000);

}



// Loop function
void loop() {

        robot.Go_Forward_30cm();
        delay(2000);
        robot.Go_Right_90degrees();
        delay(2000);
        robot.Go_Forward_30cm();
        delay(2000);
        robot.Go_Left_90degrees();
        delay(2000);
        robot.Go_Forward_30cm();
        delay(2000);

}
