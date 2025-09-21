################################################ Image Recogntion Algorythm ###############################################


#Including needed libraries

import cv2                       #Libary for image processing
import numpy as np               #Libary for matrix processing
import pytesseract as tess       #Libary for character recognition
#tess.pytesseract.tesseract_cmd = r'C:\Program Files\Tesseract-OCR\tesseract.exe' #Installed software "Tesseract" directory path
from PIL import Image            #Python Image Library
import time                      #LIbrary for countig time
from picamera import PiCamera    #Raspberry camera library
from picamera.array import PiRGBArray

import cv2 
import pytesseract as tess       #Libary for character recognition
from picamera.array import PiRGBArray
from picamera import PiCamera
import time
import numpy as np               #Libary for matrix processing



##################################################### FUNCTION DEFINITIONS ################################################
# Adding custom options for tesseract configuration

custom_config = r'--oem 3 --psm 6'

camera = PiCamera()
camera.resolution = (640, 480)
camera.framerate = 60
rawCapture = PiRGBArray(camera, size=(640, 480))

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

#########################################################################################

def recogniseCharacter(frame):

    frame = cv2.imread("/home/pi/Desktop/v.3.0_ImageRecognition/Image Recognition/target.png")
    #cv2.imshow("Greyscale img", frame)
    #Image preprocessing

    gray = get_grayscale(frame)
    #cv2.imshow('Grayscaled image',gray )
    k = cv2.waitKey(0)
    if k == 27:         # wait for ESC key to exit
        cv2.destroyAllWindows()
        
    thresh = thresholding(gray)
    #cv2.imshow('Theresholded image',thresh  )
    k = cv2.waitKey(0)
    if k == 27:         # wait for ESC key to exit
        cv2.destroyAllWindows()
        
  
  #  openFilter = opening(openFilter)
    #cv2.imshow('Opening image',opening )
   # k = cv2.waitKey(0)
    #if k == 27:         # wait for ESC key to exit
     #   cv2.destroyAllWindows()
      
     
        
    #Extracting charcter from image
    text = tess.image_to_string(thresh, config=custom_config)

    #Print founded chharacter
    print('Character which is recognised is: "',text,'"')

 
def pixelCounter(image):

    width, height=image.size
    print("Width ",width,", Height ", height)
    imagePixelNumber=width*height
    return imagePixelNumber
    print("Total image number of pixel is ", imagePixelNumber)
    

def redColorFilter(hsv,image):

    imagePixelNumber=pixelCounter(image)
    #print("Total image number of pixel is ", imagePixelNumber)
    
    #Matrix which contains minimal HSV values for red color
    minRedIntervalValues = np.array([174, 0, 0])
    #Matrix which contains maximal HSV values for red color
    maxRedIntervalValues= np.array([255,237,253])

    #Matrix which filter image
    redMask = cv2.inRange(hsv,minRedIntervalValues , maxRedIntervalValues)
    #Final filtered image, matrix format 
    #finall_Image = cv2.bitwise_and(frame, frame, mask=redMask)

    #Opens three image windows: image "frame", image "mask" and finall image "res"
    #cv2.imshow("Red Mask", redMask)

    #Nuber of white pixels on the image red color filter
    numberOfRedPixel=cv2.countNonZero(redMask)
    #Percent of white pixels on the image Red color filter
    numberOfRedPixelPercent=(numberOfRedPixel/imagePixelNumber)*100
    
    print("Recognised color is Red with ",round(numberOfRedPixelPercent,2),"%")

 
    
def orangeColorFilter(hsv,image):

    imagePixelNumber=pixelCounter(image)
    #print("Total image number of pixel is ", imagePixelNumber)
 
    #Matrix which contains minimal HSV values for Orange color
    minOrangeIntervalValues = np.array([4, 39, 0])
    #Matrix which contains maximal HSV values for Orange color
    maxOrangeIntervalValues= np.array([11, 255, 255])

    #Matrix which filter image
    OrangeMask = cv2.inRange(hsv,minOrangeIntervalValues , maxOrangeIntervalValues)
    #Final filteOrange image, matrix format 
    #finall_Image = cv2.bitwise_and(frame, frame, mask=OrangeMask)

    #Opens three image windows: image "frame", image "mask" and finall image "res"
    #cv2.imshow("Orange Mask", OrangeMask)

    #Nuber of white pixels on the image Orange color filter
    numberOfOrangePixel=cv2.countNonZero(OrangeMask)
    #Percent of white pixels on the image Orange color filter
    numberOfOrangePixelPercent=(numberOfOrangePixel/imagePixelNumber)*100
    
    print("Recognised color is Orange with ",round(numberOfOrangePixelPercent,2),"%")
 
    

def greenColorFilter(hsv,image):

    imagePixelNumber=pixelCounter(image)
    #print("Total image number of pixel is ", imagePixelNumber)

    #Matrix which contains minimal HSV values for Green color
    minGreenIntervalValues = np.array([38, 29, 0])
    #Matrix which contains maximal HSV values for Green color
    maxGreenIntervalValues= np.array([74, 255, 255])

    #Matrix which filter image
    GreenMask = cv2.inRange(hsv,minGreenIntervalValues , maxGreenIntervalValues)
    #Final filteGreen image, matrix format 
    #finall_Image = cv2.bitwise_and(frame, frame, mask=GreenMask)

    #Opens three image windows: image "frame", image "mask" and finall image "res"
    #cv2.imshow("Green Mask", GreenMask)

    #Nuber of white pixels on the image Green color filter
    numberOfGreenPixel=cv2.countNonZero(GreenMask)
    #Percent of white pixels on the image Green color filter
    numberOfGreenPixelPercent=(numberOfGreenPixel/imagePixelNumber)*100
    
    print("Recognised color is Green with ",round(numberOfGreenPixelPercent,2),"%")

def showInputImage(frame):
    
    cv2.imshow("Ulazna slika", frame)
    #cv2.imshow("Konacna slika", finall_Image)
    

#################################################### MAIN LOOP #################################
for frame in camera.capture_continuous(rawCapture, format="bgr", use_video_port=False,burst=False):
    
    start_time=time.time()
    image=frame
    imageArray=image.array
    cv2.imshow("Frame", imageArray)
    key = cv2.waitKey(1) & 0xFF
    picture_taken_time=time.time()
    
    print('Spended time for taking picture', picture_taken_time-start_time)


    #Color recognition
    hsv = cv2.cvtColor(imageArray, cv2.COLOR_BGR2HSV)
    redColorFilter(hsv,image)
    greenColorFilter(hsv,image)
    orangeColorFilter(hsv,image)
    color_recognised_time=time.time()
    print('Spended time for color recognitio', color_recognised_time-picture_taken_time)
    

    #Preprocessing for Character Recognition
    
    gray = get_grayscale(imageArray)
    #showAndWaitEscKey("Grayscaled image", gray)
        
    thresh = thresholding(gray)
    #showAndWaitEscKey('Theresholded image',thresh  )
        
    openFilter = opening(thresh)
    #showAndWaitEscKey('Opening image',openFilter )
        
    #Extracting charcter from image
    text = tess.image_to_string(openFilter, config=custom_config)
    #Print founded chharacter
    print('Character which is recognised is: "',text,'"')

    rawCapture.truncate(0)
    end_time=time.time()
    print('Spended time for tesseract', end_time-picture_taken_time)
    print('\n')
    
    #Exit program when key "ESC" is pressed
    key = cv2.waitKey(1)
    if key == 27:
       break

cv2.destroyAllWindows()
    
  
 