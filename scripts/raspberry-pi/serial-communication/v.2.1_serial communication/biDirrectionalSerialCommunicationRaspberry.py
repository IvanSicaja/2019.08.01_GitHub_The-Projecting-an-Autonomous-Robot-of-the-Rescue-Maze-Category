import serial
import time


if __name__ == '__main__':
    ser = serial.Serial('/dev/ttyACM1', 9600)
    ser.flush()
    while True:
        if ser.in_waiting > 0:
            # Slanje texta ""Hello from Raspberry Pi!" na Arduino
            ser.write(b'HRP!\n')
            
            # Ocitanje texa koji dolazi na Raspberry Pi
            line = ser.readline().decode('utf-8').rstrip()
            print(line)
            if line=='Hello from Arduino!':
                print('Yes!')
  
