
#include "Robot_Gibanje.h"

ROBOT_GIBANJE robot;


void setup() {



        Serial.begin(115200); // Start communication with a computer connected to Teensy via a USB cable

        robot.SetupZaSveKomponente();

        delay(1000);

}



// Loop function
void loop() {
        Serial.print("Prednji: ");
        Serial.println(robot.Read_Forward_Distance());
        delay(2000);
        Serial.print("Lijevi1: ");
        Serial.println(robot.Read_Left1_Distance());
        delay(2000);
        Serial.print("Lijevi2: ");
        Serial.println(robot.Read_Left2_Distance());
        delay(2000);
        Serial.print("Desni1: ");
        Serial.println(robot.Read_Right1_Distance());
        delay(2000);
        Serial.print("Desni2: ");
        Serial.println(robot.Read_Right2_Distance());
        delay(2000);
}
