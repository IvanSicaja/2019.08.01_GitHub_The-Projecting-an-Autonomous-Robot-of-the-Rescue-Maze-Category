#include <boarddefs.h>
#include <IRremote.h>
#include <IRremoteInt.h>
#include <ir_Lego_PF_BitStreamEncoder.h>

#define IR_ADVANCE         0x00FF18E7       //code from IR controller "▲" button
#define IR_BACK            0x00FF4AB5       //code from IR controller "▼" button
#define IR_RIGHT           0x00FF5AA5       //code from IR controller ">" button
#define IR_LEFT            0x00FF10EF       //code from IR controller "<" button
#define IR_STOP            0x00FF38C7       //code from IR controller "OK" button
#define IR_AUTONOMUS_MODE  0x00FFB04F       //code from IR controller "#" button

const int RECV_PIN = 7;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup(){
  Serial.begin(9600);
  irrecv.enableIRIn();
 
}

void loop(){
  if (irrecv.decode(&results)){

      if(results.value==IR_ADVANCE){
      Serial.println("UP");
      }
      
      else if(results.value==IR_BACK){
      Serial.println("DOWN");
      }
      
      else if(results.value==IR_LEFT ){
      Serial.println("LEFT");
      }
      
      else if(results.value==IR_RIGHT){
      Serial.println("RIGHT");
      }
      
      else if(results.value==IR_STOP){
      Serial.println("STOP");
      }

      else if(results.value==IR_AUTONOMUS_MODE){
      Serial.println("AUTONOMUS_MODE");
      }

      results.value=0;
      irrecv.resume();
  }
}
