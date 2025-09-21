#Libraries
import RPi.GPIO as GPIO
from time import sleep
import time

# Define a function 
def on_off_in_time_interval(devices_pin,duration_interval_in_milisecnods):
    
    time_1=time.time()
    time_2=time.time()
    
    while((time_2-time_1)<(duration_interval_in_milisecnods)):
        
        time_2=time.time()
        
        time_3=time.time()
        time_4=time.time()
        
        while((time_4-time_3)<(0.25)):
            GPIO.output(devices_pin,GPIO.HIGH)
            time_4=time.time()
            
        time_3=time.time()
        time_4=time.time()
        
        while((time_4-time_3)<(0.25)):
            GPIO.output(devices_pin,GPIO.LOW)
            time_4=time.time()


#Disable warnings (optional)
GPIO.setwarnings(False)
#Select GPIO mode
GPIO.setmode(GPIO.BCM)
#Set buzzer - pin 23 as output
buzzer=21 
GPIO.setup(buzzer,GPIO.OUT)
#Run forever loop
on_off_in_time_interval(buzzer,5)
    
    

