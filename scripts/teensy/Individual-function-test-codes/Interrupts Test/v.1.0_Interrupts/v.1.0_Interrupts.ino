const byte interruptPin = 23;
volatile byte state = LOW;


/*

LOW to trigger the interrupt whenever the pin is low,

CHANGE to trigger the interrupt whenever the pin changes value

RISING to trigger when the pin goes from low to high,

FALLING for when the pin goes from high to low.

The Due, Zero and MKR1000 boards allow also:

HIGH to trigger the interrupt whenever the pin is high.
*/

void setup() {
  Serial.begin(9600);
  pinMode(interruptPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(interruptPin), function, LOW);

}

void loop() {
  
  Serial.println("Nista.");
  delay(200);
  
}

void function() {

  Serial.println("Arbajtuje pajdo");
  delay(20);
  
}
