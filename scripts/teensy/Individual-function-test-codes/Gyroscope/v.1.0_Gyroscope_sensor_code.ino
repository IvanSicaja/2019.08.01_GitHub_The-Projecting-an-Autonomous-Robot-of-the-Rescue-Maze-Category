//collects data from an analog sensor

int sensorpin_yaw = 36;     // analog pin used to connect to the gyroscope sensor
int sensorpin_roll = 37;  
int sensorpin_pitch= 38;  

                       // variable to store the values from sensor(initially zero
 
int roll = 0;         // X-axis
int pitch= 0;         // Y-axis
int yaw = 0;          // Z-axis

void setup()
{
  Serial.begin(9600);               // starts the serial monitor
}
 
void loop()
{                                    // reads the value of the gyroscope sensor
roll = analogRead(sensorpin_roll); 
pitch = analogRead(sensorpin_pitch); 
yaw = analogRead(sensorpin_yaw);  

                                           // prints the value of the sensor  
      
      Serial.print(" Rotacija po X-osi: ");
      Serial.print(roll); 
      Serial.print(",");  
      Serial.print(" Y-osi:  "); 
      Serial.print(pitch);  
      Serial.print(",");  
      Serial.print(" Z-osi:  "); 
      Serial.print(yaw);            
      Serial.println(" degree.");
       
  delay(400);                    // wait for this much time before printing next value
}
