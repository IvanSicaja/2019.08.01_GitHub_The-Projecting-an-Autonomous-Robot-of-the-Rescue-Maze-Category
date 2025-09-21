
#include "Robot_Gibanje.h"

ROBOT_GIBANJE mojrobot;


void setup() {



        Serial.begin(115200); // Start communication with a computer connected to Teensy via a USB cable

        mojrobot.SetupZaSveKomponente();

        delay(1000);

}



// Loop function
void loop() {
        delay(1000);
        mojrobot.Go_Forward_30cm();
        delay(4000);
        mojrobot.Go_Left_90degrees();
        delay(5000);
}
