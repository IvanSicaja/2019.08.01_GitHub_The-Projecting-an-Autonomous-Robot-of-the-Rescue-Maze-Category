void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  
  Serial.begin(9600);

}

void loop() {
  
    //Slanje texta na Serijski port Raspberry-a
  Serial.println("Hello from Arduino!"); 
  //delay(200);

    
  //Ocitanje texa koji dolazi na Arduino serijski port
  if (Serial.available() > 0) {
    
  String data = Serial.readStringUntil('\n');
  
  if (data.substring(0) == "HRP!") {
    Serial.println("FOUND");

    }

   //Serial.print("You sent me: ");

 //  Serial.println(data);

 }

}
