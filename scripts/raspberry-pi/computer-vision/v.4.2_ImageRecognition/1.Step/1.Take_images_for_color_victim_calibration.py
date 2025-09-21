from picamera import PiCamera
import cv2
cap = cv2.VideoCapture(0)



while True:
    _, img = cap.read()
    cv2.imshow("slika", img)
    if cv2.waitKey(5) != -1:
        break
cap.release()
cv2.destroyAllWindows()

while True:
    char = input()

    if(char=="r"):
        print ("Pressed r.")
        camera = PiCamera()
        camera.capture("/home/pi/Desktop/v.4.2_ImageRecognition/1.Step/Color_victims_images_for_calibration/Red_victim.png")
        print("Done.")
        break
    
    if(char=="y"):
        print ("Pressed y.")
        camera = PiCamera()
        camera.capture("/home/pi/Desktop/v.4.2_ImageRecognition/1.Step/Color_victims_images_for_calibration/Yellow_victim.png")
        print("Done.")
        break
    
    if(char=="g"):
        print ("pressed g")
        camera = PiCamera()
        camera.capture("/home/pi/Desktop/v.4.2_ImageRecognition/1.Step/Color_victims_images_for_calibration/Green_victim.png")
        print("Done.")
        break


