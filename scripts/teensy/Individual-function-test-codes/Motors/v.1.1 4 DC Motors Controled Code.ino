#define SPEED_1     35 // 1. motor, pin za brzinu motora
#define DIRECTION_1 36 // 1. motor, pin za smjer vrtnje motora

void setup() {
  pinMode(SPEED_1, OUTPUT);
  pinMode(DIRECTION_1, OUTPUT); 

}

void loop() {

int brzina_smjer,brzina,smjer;   // brzina_smjer moze ici u rasponu od -10 do 10. 
                                 //Ako je -10 rotacija motora je ulijevo punom brzinom.
                                 //Ako je 10 rotacija motora je u smjeru kazaljke na satu punom brzinom.

 brzina_smjer = 7;

if( brzina_smjer>0 )
{
  smjer =255;
brzina = map (brzina_smjer,0,10,255,0);

  }
  else if ( brzina_smjer<0)
  
  {
    smjer = 0;
    brzina = map (brzina_smjer, -10,0,0,255);
    }
    
else if (brzina_smjer=0)
{
  smjer = 0;
  brzina = 0;
  }

  
analogWrite(DIRECTION_1, smjer);
analogWrite(SPEED_1, brzina);

}
