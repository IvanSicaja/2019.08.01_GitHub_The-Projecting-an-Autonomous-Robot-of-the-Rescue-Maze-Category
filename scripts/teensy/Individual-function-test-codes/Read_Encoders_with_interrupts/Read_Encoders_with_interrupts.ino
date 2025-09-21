#include <util/atomic.h> // For the ATOMIC_BLOCK macro

#define ENCA 56 // YELLOW
#define ENCB 57 // WHITE

volatile int posi = 0; // specify posi as volatile: https://www.arduino.cc/reference/en/language/variables/variable-scope-qualifiers/volatile/
int i = 0;

void setup() {
  Serial.begin(9600);
  pinMode(ENCA, INPUT);
  pinMode(ENCB, INPUT);
  attachInterrupt(digitalPinToInterrupt(ENCA), readEncoder, RISING);
   
}

void loop() {
  // Read the position in an atomic block to avoid a potential
  // misread if the interrupt coincides with this code running
  // see: https://www.arduino.cc/reference/en/language/variables/variable-scope-qualifiers/volatile/
  
  int pos = 0;

  //ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {

    pos = posi;
    if (pos > 50) {
      posi = 0;
      i=i+1;
  //  }

  }

  Serial.println(pos);
  Serial.println(i);
}

void readEncoder() {
  int b = digitalRead(ENCB);
  if (b > 0) {
    posi++;
  }
  else {
    posi--;
  }
}
