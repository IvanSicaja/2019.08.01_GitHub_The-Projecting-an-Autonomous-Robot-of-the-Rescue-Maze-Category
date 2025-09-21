unsigned long startMillis;  //some global variables available anywhere in the program
unsigned long currentMillis;
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  
  Serial.begin(9600);
 startMillis = millis();

}

void loop() {
  
    //Slanje texta na Serijski port Raspberry-a

    currentMillis = millis();
    //Serial.println(startMillis );
    //Serial.println(currentMillis);
 

    if ((currentMillis-startMillis)>3000)
    {
       Serial.println("Hello from Arduino!"); 
       startMillis=currentMillis;
    }
  
  //delay(200);

    
  //Ocitanje texa koji dolazi na Arduino serijski port
  if (Serial.available() > 0) {
    
  String data = Serial.readStringUntil('\n');
  
  if (data.substring(0) == "SFND") {
    Serial.println("FOUND");

    }

   //Serial.print("You sent me: ");

 //  Serial.println(data);

 }

}
