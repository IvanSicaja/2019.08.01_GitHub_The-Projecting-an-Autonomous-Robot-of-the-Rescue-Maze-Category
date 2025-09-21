import RPi.GPIO as GPIO

import time

LED=16

GPIO.setmode(GPIO.BCM)

GPIO.setwarnings(False)

GPIO.setup(LED,GPIO.OUT)

while True:

    print ('LED on')
    
    GPIO.output(LED,GPIO.HIGH)
    
    time.sleep(1)
    
    print ('LED off')
    
    GPIO.output(LED,GPIO.LOW)
    time.sleep(1)

