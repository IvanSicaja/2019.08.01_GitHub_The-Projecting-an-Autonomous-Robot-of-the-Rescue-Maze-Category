#Including needed libraries

import cv2                       #Libary for image processing
import numpy as np               #Libary for matrix processing
import pytesseract as tess       #Libary for character recognition
tess.pytesseract.tesseract_cmd = r'C:\Program Files\Tesseract-OCR\tesseract.exe' #Installed software "Tesseract" directory path
from PIL import Image            #Python Image Library


########################################################################################################################


#Load image like matrix
frame = cv2.imread('colorImg.png')
#Read image size
image=Image.open('colorImg.png')
width, height=image.size
#print("Width ",width,", Height ", height)
imagePixelNumber=width*height
#print("Total image number of pixel is ", imagePixelNumber)

#Try to find character on image
text = tess.image_to_string(frame)

#Print founded chharacter
print('\nCharacter which is recognised is: "',text,'"')


#######################################################################################################################

#Convert image color values to HSV format
hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

#################################### RED COLOR FILTER ######################################
 
#Matrix which contains minimal HSV values for red color
minRedIntervalValues = np.array([174, 0, 0])
#Matrix which contains maximal HSV values for red color
maxRedIntervalValues= np.array([255,237,253])

#Matrix which filter image
redMask = cv2.inRange(hsv,minRedIntervalValues , maxRedIntervalValues)
#Final filtered image, matrix format 
#finall_Image = cv2.bitwise_and(frame, frame, mask=redMask)

#Opens three image windows: image "frame", image "mask" and finall image "res"
cv2.imshow("Red Mask", redMask)

#Nuber of white pixels on the image red color filter
numberOfRedPixel=cv2.countNonZero(redMask)
#Percent of white pixels on the image Red color filter
numberOfRedPixelPercent=(numberOfRedPixel/imagePixelNumber)*100
print("Recognised color is Red with ",round(numberOfRedPixelPercent,2),"%")


#################################### ORANGE COLOR FILTER ######################################
 

#Matrix which contains minimal HSV values for Orange color
minOrangeIntervalValues = np.array([4, 39, 0])
#Matrix which contains maximal HSV values for Orange color
maxOrangeIntervalValues= np.array([11, 255, 255])

#Matrix which filter image
OrangeMask = cv2.inRange(hsv,minOrangeIntervalValues , maxOrangeIntervalValues)
#Final filteOrange image, matrix format 
#finall_Image = cv2.bitwise_and(frame, frame, mask=OrangeMask)

#Opens three image windows: image "frame", image "mask" and finall image "res"
cv2.imshow("Orange Mask", OrangeMask)

#Nuber of white pixels on the image Orange color filter
numberOfOrangePixel=cv2.countNonZero(OrangeMask)
#Percent of white pixels on the image Orange color filter
numberOfOrangePixelPercent=(numberOfOrangePixel/imagePixelNumber)*100
print("Recognised color is Orange with ",round(numberOfOrangePixelPercent,2),"%")


#################################### GREEN COLOR FILTER ######################################

 
#Matrix which contains minimal HSV values for Green color
minGreenIntervalValues = np.array([28, 200, 0])
#Matrix which contains maximal HSV values for Green color
maxGreenIntervalValues= np.array([72, 255, 255])

#Matrix which filter image
GreenMask = cv2.inRange(hsv,minGreenIntervalValues , maxGreenIntervalValues)
#Final filteGreen image, matrix format 
#finall_Image = cv2.bitwise_and(frame, frame, mask=GreenMask)

#Opens three image windows: image "frame", image "mask" and finall image "res"
cv2.imshow("Green Mask", GreenMask)

#Nuber of white pixels on the image Green color filter
numberOfGreenPixel=cv2.countNonZero(GreenMask)
#Percent of white pixels on the image Green color filter
numberOfGreenPixelPercent=(numberOfGreenPixel/imagePixelNumber)*100
print("Recognised color is Green with ",round(numberOfGreenPixelPercent,2),"%")

#######################################################################################################################


cv2.imshow("Ulazna slika", frame)
#cv2.imshow("Konacna slika", finall_Image)

while True:
    #Exit program when key "ESC" is pressed
    key = cv2.waitKey(1)
    if key == 27:
        break

cv2.destroyAllWindows()

 