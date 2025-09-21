################################################ Image Recogntion Algorythm ###############################################


#Including needed libraries

import cv2                       #Libary for image processing
import numpy as np               #Libary for matrix processing
import pytesseract as tess       #Libary for character recognition
#tess.pytesseract.tesseract_cmd = r'C:\Program Files\Tesseract-OCR\tesseract.exe' #Installed software "Tesseract" directory path
from PIL import Image            #Python Image Library
import time                      #LIbrary for countig time
from picamera import PiCamera    #Raspberry camera library


##################################################### FUNCTION DEFINITIONS ################################################
# Adding custom options for tesseract configuration
custom_config = r'--oem 3 --psm 6'

def takePicture(camera):
    camera.resolution=(640,480)                                                         #Set image resolution
    camera.framerate = 60
    camera.capture("/home/pi/Desktop/v.3.0_ImageRecognition/Image Recognition/target.png")    #Take picture
    print("Picture taken.")
    
#Predprocessing image functions definition

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
    #print("Width ",width,", Height ", height)
    imagePixelNumber=width*height
    return imagePixelNumber
    #print("Total image number of pixel is ", imagePixelNumber)
    

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
    
    ###print("Recognised color is Red with ",round(numberOfRedPixelPercent,2),"%")

 
    
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
    
    ###print("Recognised color is Orange with ",round(numberOfOrangePixelPercent,2),"%")
 
    

def greenColorFilter(hsv,image):

    imagePixelNumber=pixelCounter(image)
    #print("Total image number of pixel is ", imagePixelNumber)

    #Matrix which contains minimal HSV values for Green color
    minGreenIntervalValues = np.array([28, 200, 0])
    #Matrix which contains maximal HSV values for Green color
    maxGreenIntervalValues= np.array([72, 255, 255])

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
    
    ###print("Recognised color is Green with ",round(numberOfGreenPixelPercent,2),"%")

def showInputImage(frame):
    
    cv2.imshow("Ulazna slika", frame)
    #cv2.imshow("Konacna slika", finall_Image)


##################################################### PROGRAM START HERE #################################################

start_time=time.time()
print("Time_0", start_time)
counter=0                              #Counter which tells us how many times the image is taken

camera=PiCamera()                      #Initialize Camera module
 
time_1=time.time()
print("Time_1", time_1)

while True:

    takePicture(camera)
    time_2=time.time()
    print("pictureTaken       ",time_2-time_1)
    
    #Load image like matrix
    
    frame = cv2.imread('/home/pi/Desktop/v.3.0_ImageRecognition/Image Recognition/target.png')
    time_1=time.time()
    print("imread             ", time_1)

    #Read image size
    image=Image.open('/home/pi/Desktop/v.3.0_ImageRecognition/Image Recognition/target.png')
    time_1=time.time()
    print("imageOpen          ", time_1)

    #Convert image color values to HSV format
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    time_1=time.time()
    print("convertToHSV       ",time_1)
 
    recogniseCharacter(frame)
    time_2=time.time()
    print("recogniseCharacter ",time_2-time_1)

    pixelCounter(image)
    time_1=time.time()
    print("pixelCounter       ",time_1)  

    redColorFilter(hsv,image)
    time_1=time.time() 
    print("redColorFilter     ",time_1)  

    orangeColorFilter(hsv,image)
    time_1=time.time() 
    print("orangeColorFilter  ",time_1) 

    greenColorFilter(hsv,image)
    time_1=time.time() 
    print("greenColorFilter   ",time_1) 

    #showInputImage(frame)
    #time_1=time.time() 
    #print("showInputImage     ",time_1) 

    counter=counter+1

    print("\nCunter", counter)
    
    end_time=time.time()

    timeInterval=end_time-start_time

    '''if timeInterval >=1000:
        print("End.")
        break
        '''

    #Exit program when key "ESC" is pressed
    key = cv2.waitKey(1)
    if key == 27:
       break
    

cv2.destroyAllWindows()

 