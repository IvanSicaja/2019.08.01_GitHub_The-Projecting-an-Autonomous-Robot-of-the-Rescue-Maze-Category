//Initializing LED Pin
int led_pin = 3;
void setup() {
  //Declaring LED pin as output
  pinMode(led_pin, OUTPUT);
}
void loop() {
digitalWrite(led_pin,HIGH);
delay(5000);
digitalWrite(led_pin,LOW);
delay(5000);
}
