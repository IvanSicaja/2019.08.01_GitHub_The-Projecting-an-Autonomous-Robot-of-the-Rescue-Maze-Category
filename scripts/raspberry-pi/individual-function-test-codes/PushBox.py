#Libraries
import RPi.GPIO as GPIO
from time import sleep
import time

# Define a function 
def pushBox(PIN1,PIN2,boxes_amount,delay):
    
    time_1=time.time()
    time_2=time.time()
    boxCounter=0
    
    while boxCounter<boxes_amount:
        boxCounter=boxCounter+1
        time_2=time.time()
        
        time_3=time.time()
        time_4=time.time()
        
        while((time_4-time_3)<(0.1)):
            GPIO.output(PIN1,GPIO.LOW)
            GPIO.output(PIN2,GPIO.HIGH)
            time_4=time.time()
            
        time_3=time.time()
        time_4=time.time()
        
        while((time_4-time_3)<(delay)):
            GPIO.output(PIN1,GPIO.LOW)
            GPIO.output(PIN2,GPIO.LOW)
            time_4=time.time()
            
ElectroMotor_PIN1=26
ElectroMotor_PIN2=19
 

#Disable warnings (optional)
GPIO.setwarnings(False)
#Select GPIO mode
GPIO.setmode(GPIO.BCM)
#Set buzzer - pin 23 as output
GPIO.setup(ElectroMotor_PIN1,GPIO.OUT)
#Run forever loop

#Disable warnings (optional)
GPIO.setwarnings(False)
#Select GPIO mode
GPIO.setmode(GPIO.BCM)
#Set buzzer - pin 23 as output
GPIO.setup(ElectroMotor_PIN2,GPIO.OUT)
#Run forever loop


pushBox(ElectroMotor_PIN1,ElectroMotor_PIN2,2,1)
    
    

