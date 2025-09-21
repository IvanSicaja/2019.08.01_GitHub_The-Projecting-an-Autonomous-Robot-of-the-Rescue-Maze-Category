
#define SPEED_1     2 // 1. motor, pin za brzinu motora
#define DIRECTION_1 3 // 1. motor, pin za smjer vrtnje motora
#define SPEED_2     4 // 2. motor, pin za brzinu motora
#define DIRECTION_2 5 // 2. motor, pin za smjer vrtnje motora
#define SPEED_3     6 // 3. motor, pin za brzinu motora
#define DIRECTION_3 7 // 3. motor, pin za smjer vrtnje motora
#define SPEED_4     8 // 4. motor, pin za brzinu motora
#define DIRECTION_4 9 // 4. motor, pin za smjer vrtnje motora


  void Go_forward();
  void Go_back();
  void Stop_robot();

  
 void Go_forward(){

    digitalWrite(DIRECTION_1, 0);  
    digitalWrite(SPEED_1, 255);  
    
    digitalWrite(DIRECTION_2, 0);  
    digitalWrite(SPEED_2, 255);  
    
    digitalWrite(DIRECTION_3, 0);  
    digitalWrite(SPEED_3, 255);  
    
    digitalWrite(DIRECTION_4, 0);  
    digitalWrite(SPEED_4, 255);  
  }

  void Go_back(){

    digitalWrite(DIRECTION_1, 255);  
    digitalWrite(SPEED_1, 0);  
    
    digitalWrite(DIRECTION_2, 255);  
    digitalWrite(SPEED_2, 0);  
    
    digitalWrite(DIRECTION_3, 255);  
    digitalWrite(SPEED_3, 0);  
    
    digitalWrite(DIRECTION_4, 255);  
    digitalWrite(SPEED_4, 0);  
    
    }
  
   void Stop_robot(){

    digitalWrite(DIRECTION_1, 0);  
    digitalWrite(SPEED_1, 0);  
    
    digitalWrite(DIRECTION_2, 0);  
    digitalWrite(SPEED_2, 0);  
    
    digitalWrite(DIRECTION_3, 0);  
    digitalWrite(SPEED_3, 0);  
    
    digitalWrite(DIRECTION_4, 0);  
    digitalWrite(SPEED_4, 0); 
    
    }
 
void setup() {
  
  pinMode(SPEED_1, OUTPUT);
  pinMode(DIRECTION_1, OUTPUT); 
  
  pinMode(SPEED_2, OUTPUT);
  pinMode(DIRECTION_2, OUTPUT); 
  
  pinMode(SPEED_3, OUTPUT);
  pinMode(DIRECTION_3, OUTPUT); 
  
  pinMode(SPEED_4, OUTPUT);
  pinMode(DIRECTION_4, OUTPUT); 

   
}

void loop() {
  
  Go_forward();
  delay(5000);
  Go_back();
  delay(5000);
  Stop_robot();
  delay(5000);

}
