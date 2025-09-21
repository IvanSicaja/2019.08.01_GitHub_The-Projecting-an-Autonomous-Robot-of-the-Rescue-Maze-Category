import picamera

print("Our's script is running")

with picamera.PiCamera() as camera:
    camera.resolution=(1280,720)
    camera.capture("/home/pi/Desktop/ImageRecognition/v.1.0_CameraPi/targets.jpg")
    print("Picture taken")