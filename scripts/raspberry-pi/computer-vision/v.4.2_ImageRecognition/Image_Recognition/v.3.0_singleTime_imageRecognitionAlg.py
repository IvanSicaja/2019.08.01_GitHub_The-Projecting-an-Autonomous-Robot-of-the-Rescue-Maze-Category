#Including needed libraries

import cv2                       #Libary for image processing
import numpy as np               #Libary for matrix processing
import pytesseract as tess       #Libary for character recognition
#tess.pytesseract.tesseract_cmd = r'/usr/bin/tesseract.exe' #Installed software "Tesseract" directory path
from PIL import Image            #Python Image Library


########################################################################################################################


#Load image like matrix
frame = cv2.imread('/home/pi/Desktop/v.3.0_ImageRecognition/Image Recognition/target.png')

# Adding custom options
#Moj život se dijeli prije i poslije ove linije koda
#Nisam ni slutio da jedna linija koda može učiniti osobu toliko sretnim :)
custom_config = r'--oem 3 --psm 6'


#Read image size
image=Image.open('/home/pi/Desktop/v.3.0_ImageRecognition/Image Recognition/target.png')
width, height=image.size
#print("Width ",width,", Height ", height)
imagePixelNumber=width*height
#print("Total image number of pixel is ", imagePixelNumber)



#Image preprocessing needed for Tesseract
##############################################################################################

#Predprocessing functions definition

# get grayscale image
def get_grayscale(image):
    return cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

# noise remove function
def remove_noise(image):
    return cv2.medianBlur(image,5)
 
#thresholding
def thresholding(image):
    return cv2.threshold(image, 0, 255, cv2.THRESH_BINARY + cv2.THRESH_OTSU)[1]

#dilation
def dilate(image):
    kernel = np.ones((5,5),np.uint8)
    return cv2.dilate(image, kernel, iterations = 1)
    
#erosion
def erode(image):
    kernel = np.ones((5,5),np.uint8)
    return cv2.erode(image, kernel, iterations = 1)

#opening - erosion followed by dilation
def opening(image):
    kernel = np.ones((5,5),np.uint8)
    return cv2.morphologyEx(image, cv2.MORPH_OPEN, kernel)

#canny edge detection
def canny(image):
    return cv2.Canny(image, 100, 200)


#template matching
def match_template(image, template):
    return cv2.matchTemplate(image, template, cv2.TM_CCOEFF_NORMED) 



#Image preprocessing

gray = get_grayscale(frame)
cv2.imshow('Grayscaled image',gray )
k = cv2.waitKey(0)
if k == 27:         # wait for ESC key to exit
    cv2.destroyAllWindows()
    
thresh = thresholding(gray)
cv2.imshow('Theresholded image',thresh  )
k = cv2.waitKey(0)
if k == 27:         # wait for ESC key to exit
    cv2.destroyAllWindows()
    
opening = opening(thresh )
cv2.imshow('Opening image',opening )
k = cv2.waitKey(0)
if k == 27:         # wait for ESC key to exit
    cv2.destroyAllWindows()
    
 
#Extracting charcter from image
text = tess.image_to_string(opening, config=custom_config)

#Print founded chharacter
print('\nCharacter which is recognised is: "',text,'"')

################################################## COLOR RECOGNITION ####################################################

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

 