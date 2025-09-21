#define SPEED_1     35 // 1. motor, pin za brzinu motora
#define DIRECTION_1 36 // 1. motor, pin za smjer vrtnje motora
#define SPEED_2     37 // 2. motor, pin za brzinu motora
#define DIRECTION_2 38 // 2. motor, pin za smjer vrtnje motora

void setup() {
  pinMode(SPEED_1, OUTPUT);
  pinMode(DIRECTION_1, OUTPUT); 
  pinMode(SPEED_2, OUTPUT); 
  pinMode(DIRECTION_2, OUTPUT);
}

void loop() {
digitalWrite(DIRECTION_1, HIGH); // Smjer vrtnje motora, može biti LOW (suprotno od smjera kazaljke) ili HIGH (u smjeru kazaljke).
analogWrite(SPEED_1, 0); // Brzina motora u rasponu od 0-255. Ako je smjer vrtnje LOW onda je maksimalna brzina 255, ako je smjer vrtnje HIGH onda je maksimalna brzina 0. 

digitalWrite(DIRECTION_2, LOW); // Smjer vrtnje motora, može biti LOW (suprotno od smjera kazaljke) ili HIGH (u smjeru kazaljke).
analogWrite(SPEED_2, 50); // Brzina motora u rasponu od 0-255. Ako je smjer vrtnje LOW onda je maksimalna brzina 255, ako je smjer vrtnje HIGH onda je maksimalna brzina 0. 
}
