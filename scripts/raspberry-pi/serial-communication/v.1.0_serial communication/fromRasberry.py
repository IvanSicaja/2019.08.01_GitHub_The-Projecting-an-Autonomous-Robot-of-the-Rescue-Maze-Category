import serial
import time


if __name__ == '__main__':
    ser = serial.Serial('/dev/ttyACM0', 9600)
    ser.flush()
    while True:
        if ser.in_waiting > 0:
            # Slanje texta ""Hello from Raspberry Pi!" na Arduino
            ser.write(b"Hello from Raspberry Pi!\n")
            
            # Ocitanje texa koji dolazi na Raspberry Pi
            line = ser.readline()
            print(line)
  
