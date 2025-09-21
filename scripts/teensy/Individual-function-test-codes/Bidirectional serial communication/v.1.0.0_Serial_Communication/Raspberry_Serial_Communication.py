import serial
import time


##################### Led Control ###########################

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
#############################################################################


if __name__ == '__main__':
    ser = serial.Serial('/dev/ttyACM2',9600, timeout=1)
    ser.flush()
    
    while True:
        if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8').rstrip()
            print(line)
            
            if (line == "Pajdo"):
                ledR.ChangeDutyCycle(100)
                ledG.ChangeDutyCycle(15)
                ledB.ChangeDutyCycle(0)
                
            elif (line == "Trni"):
                ledR.ChangeDutyCycle(0)
                ledG.ChangeDutyCycle(0)
                ledB.ChangeDutyCycle(0)
                
            ser.write(b'green\n')
            time.sleep(0.5)
            ser.write(b'off\n')
            time.sleep(0.5)
            
