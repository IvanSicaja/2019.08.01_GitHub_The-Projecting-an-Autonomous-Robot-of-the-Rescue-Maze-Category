String command;



#define greenLed 8



void setup() {

  Serial.begin(9600);

  pinMode(greenLed, OUTPUT);

}



void loop() {
  
  Serial.println("Pajdo");
  delay(1000);
  
  if (Serial.available()) {

    command = Serial.readStringUntil('\n');

    command.trim();

    if (command.equals("green")) {

      digitalWrite(greenLed, HIGH);
      delay(1000);
      
    }
    
    else if (command.equals("off")) {
      
      digitalWrite(greenLed, LOW);
      delay(1000);

    }
    }
  }



 


