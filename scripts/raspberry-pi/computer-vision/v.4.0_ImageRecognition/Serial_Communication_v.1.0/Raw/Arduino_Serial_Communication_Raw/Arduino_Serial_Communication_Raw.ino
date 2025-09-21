String command;



#define sensorPin A0

#define blueLed 8

#define whiteLed 9

#define redLed 10



void setup() {

  Serial.begin(9600);

  pinMode(blueLed, OUTPUT);

  pinMode(whiteLed, OUTPUT);

  pinMode(redLed, OUTPUT);

}



void loop() {

  int reading = analogRead(sensorPin);

  float voltage = reading * 5.0;

  voltage /= 1024.0;

  float temperatureC = (voltage - 0.5) * 100 ;

  float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;



  Serial.println(temperatureF); 

  if (Serial.available()) {

    command = Serial.readStringUntil('\n');

    command.trim();

    if (command.equals("white")) {

      digitalWrite(whiteLed, HIGH);

      digitalWrite(blueLed, LOW);

      digitalWrite(redLed, LOW);

    }



    else if (command.equals("blue")) {

      digitalWrite(whiteLed, LOW);

      digitalWrite(blueLed, HIGH);

      digitalWrite(redLed, LOW);

    }

    else if (command.equals("red")) {

      digitalWrite(whiteLed, LOW);

      digitalWrite(blueLed, LOW);

      digitalWrite(redLed, HIGH);

    }

    else if (command.equals("all")) {

      digitalWrite(whiteLed, HIGH);

      digitalWrite(blueLed, HIGH);

      digitalWrite(redLed, HIGH);

    }

    else if (command.equals("off")) {

      digitalWrite(whiteLed, LOW);

      digitalWrite(blueLed, LOW);

      digitalWrite(redLed, LOW);

    }

    else {

      digitalWrite(whiteLed, HIGH);

      digitalWrite(blueLed, HIGH);

      digitalWrite(redLed, HIGH);

    }

    

  }



  delay(1000);

}
