#Including needed libraries

import cv2                       #Libary for image processing
import picamera                  #Libary for Raspberry Pi Camera usage
from PIL import Image            #Python Image Library

print("Our's script is running")

with picamera.PiCamera() as camera:
    camera.resolution=(1280,720)
    camera.capture("/home/pi/Desktop/v.3.0_ImageRecognition/Image Recognition/target.png")
    print("Picture taken")







