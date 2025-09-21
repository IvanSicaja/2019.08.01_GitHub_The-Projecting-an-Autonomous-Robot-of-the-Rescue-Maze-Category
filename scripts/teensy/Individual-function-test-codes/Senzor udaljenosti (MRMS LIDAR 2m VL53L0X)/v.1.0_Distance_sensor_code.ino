//collects data from an analog sensor

int sensorpin = 35;                 // analog pin used to connect the distance sensor
int val = 0;                 // variable to store the values from sensor(initially zero)

void setup()
{
  Serial.begin(9600);               // starts the serial monitor
}
 
void loop()
{
  val = analogRead(sensorpin);
  Serial.print("Udaljenost: ");     // reads the value of the sharp sensor
  Serial.print(val/2);            // prints the value of the sensor to the serial monitor
  Serial.println(" cm."); 
  delay(400);                    // wait for this much time before printing next value
}
