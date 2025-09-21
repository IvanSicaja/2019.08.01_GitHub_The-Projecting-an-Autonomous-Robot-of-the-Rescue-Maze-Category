import serial
import time



ser = serial.Serial('/dev/ttyACM0', 9600)
ser.flush()
 
    

while 1:
    try:
        if ser.in_waiting > 0:
            # Slanje texta ""Hello from Raspberry Pi!" na Arduino
            ser.write(b"HRPI!\n")
            ser.write(b"OJ!!\n")
            ser.write(b"EJ!\n")

            # Ocitanje texa koji dolazi na Raspberry Pi
            line = ser.readline()
            print(line)
    
    except IOError:
        print ("Failed at setting port\n")
    
