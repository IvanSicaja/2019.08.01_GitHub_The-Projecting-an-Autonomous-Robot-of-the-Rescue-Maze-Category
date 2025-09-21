#define sensor 23 // Sharp IR GP2Y0A41SK0F (4-30cm, analog)

void setup() {
  Serial.begin(9600); // start the serial port
}

void loop() {
  
  // 
  //Serial.println(analogRead(sensor));
  float volts = analogRead(sensor)*0.0048828125 ;  // value from sensor * (5/1024) 
  //Serial.println(volts);
                                                                                              
  int distance = 10*(17.5*pow(volts, -0.937)); // worked out from datasheet graph  
  //delay(1000); // slow down serial port 
  Serial.println(distance);   // print the distance in millimeters

}
