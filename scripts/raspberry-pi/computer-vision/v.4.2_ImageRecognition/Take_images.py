from picamera import PiCamera
import time

camera = PiCamera()
time.sleep(2)
camera.capture("/home/pi/Desktop/img.jpg")
print("Done.")