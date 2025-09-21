import time

import RPi.GPIO as io
    
io.setmode(io.BCM)

io.setup(26,io.OUT) # make pins into an output

io.setup(19,io.OUT)

io.setup(13,io.OUT)

ledR = io.PWM(26,60) # Set up outputs as PWM @ 60Hz

ledG = io.PWM(19,60)

ledB = io.PWM(13,60)

ledR.start(0) # start off the PWM

ledG.start(0)

ledB.start(0)

print("Ctrl C to quit")
    

try:

    while(1):
    
        # Min range is 0, max PWM range is 100
    
        print("Start cycle")
        
        time.sleep(1)

        ledR.ChangeDutyCycle(100)
        
        ledG.ChangeDutyCycle(15)
        
        ledB.ChangeDutyCycle(0)
        
        time.sleep(1) # Whole cycle 8000 times this
        
        ledR.ChangeDutyCycle(0)
        
        ledG.ChangeDutyCycle(0)
        
        ledB.ChangeDutyCycle(0)
        
except KeyboardInterrupt:
    pass
    
    ledR.stop(0) #stop the PWM
    
    ledG.stop(0)
    
    ledB.stop(0)
    
    io.cleanup() # Restore default GPIO state
