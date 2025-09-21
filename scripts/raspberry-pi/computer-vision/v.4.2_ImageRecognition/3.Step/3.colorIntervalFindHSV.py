#Including needed libraries

import cv2                       #Libary for image processing
import numpy as np               #Libary for matrix processing
import pytesseract as tess       #Libary for character recognition
#tess.pytesseract.tesseract_cmd = r'/home/pi/.local/bin' #Installed software "Tesseract" directory path
from PIL import Image            #Python Image Library

def nothing(x):
    pass

#Use image like matrrix
frame = cv2.imread('/home/pi/Desktop/v.4.2_ImageRecognition/3.Step/colorMap.jpg')

#frame  = cv2.imread('/home/pi/Desktop/v.4.2_ImageRecognition/1.Step/Color_victims_images_for_calibration/Red_victim.png')
#frame  = cv2.imread('/home/pi/Desktop/v.4.2_ImageRecognition/1.Step/Color_victims_images_for_calibration/Yellow_victim.png')
#frame  = cv2.imread('/home/pi/Desktop/v.4.2_ImageRecognition/1.Step/Color_victims_images_for_calibration/Green_victim.png')

'''
#percent by which the image is resized
scale_percent = 50

#calculate the 50 percent of original dimensions
width = int(frame.shape[1] * scale_percent / 100)
height = int(frame.shape[0] * scale_percent / 100)

# dsize
dsize = (width, height)

# resize image
frame = cv2.resize(frame, dsize)
'''

def nothing(x):
    pass

#Creat trackbar for image color filterig
cv2.namedWindow("Tracking")

#Set start values of "LH","LS" and "LV" to zero (0), minimal value 
cv2.createTrackbar("LH", "Tracking", 0, 255, nothing)
cv2.createTrackbar("LS", "Tracking", 0, 255, nothing)
cv2.createTrackbar("LV", "Tracking", 0, 255, nothing)

#Set start values of "UH","US" and "UV" to 255, maxmal value 
cv2.createTrackbar("UH", "Tracking", 255, 255, nothing)
cv2.createTrackbar("US", "Tracking", 255, 255, nothing)
cv2.createTrackbar("UV", "Tracking", 255, 255, nothing)

while True:

#Convert image color values to HSV format
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

#Changeing trackbar values
    l_h = cv2.getTrackbarPos("LH", "Tracking")
    l_s = cv2.getTrackbarPos("LS", "Tracking")
    l_v = cv2.getTrackbarPos("LV", "Tracking")

    u_h = cv2.getTrackbarPos("UH", "Tracking")
    u_s = cv2.getTrackbarPos("US", "Tracking")
    u_v = cv2.getTrackbarPos("UV", "Tracking")

#Matrix which contains minimal HSV values for needed color
    l_b = np.array([l_h, l_s, l_v])
#Matrix which contains maximal HSV values for needed color
    u_b = np.array([u_h, u_s, u_v])

#Matrix which filter image
    mask = cv2.inRange(hsv, l_b, u_b)
#Final filtered image
    res = cv2.bitwise_and(frame, frame, mask=mask)

#Opens three image windows: image "frame", image "mask" and finall image "res"
    cv2.imshow("Paleta boja", frame)
    cv2.imshow("Maska", mask)
    cv2.imshow("Odabrani interval boje", res)
    

 
#Exit program when key "ESC" is pressed
    key = cv2.waitKey(1)
    if key == 27:
        break

cv2.destroyAllWindows()
