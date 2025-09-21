################################################ Image Recogntion Algorythm ###############################################


#Including needed libraries

import cv2                       #Libary for image processing
import numpy as np               #Libary for matrix processing
import pytesseract as tess       #Libary for character recognition
tess.pytesseract.tesseract_cmd = r'C:\Program Files\Tesseract-OCR\tesseract.exe' #Installed software "Tesseract" directory path
from PIL import Image            #Python Image Library
import time                      #LIbrary for countig time


##################################################### FUNCTION DEFINITIONS ################################################

def recogniseCharacter(frame):

    #frame = cv2.imread('colorImg.png',0)
    #cv2.imshow("Greyscale img", frame)

    #Try to find character on image
    text = tess.image_to_string(frame)

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

#Load image like matrix
frame = cv2.imread('colorImg.png')
time_1=time.time()
print("Time_1", time_1)

#Read image size
image=Image.open('colorImg.png')
time_2=time.time()
print("Time_2", time_2)

#Convert image color values to HSV format
hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
time_3=time.time()
print("Time_3", time_3)



while True:
    
    time_4=time.time()
    print("Start loop         ",time_4)

    recogniseCharacter(frame)
    time_5=time.time()
    print("recogniseCharacter ",time_5-time_4)

    pixelCounter(image)
    time_6=time.time()
    print("pixelCounter       ",time_6)  

    redColorFilter(hsv,image)
    time_7=time.time() 
    print("redColorFilter     ",time_7)  

    orangeColorFilter(hsv,image)
    time_8=time.time() 
    print("orangeColorFilter  ",time_8) 

    greenColorFilter(hsv,image)
    time_9=time.time() 
    print("greenColorFilter   ",time_9) 

    showInputImage(frame)
    time_10=time.time() 
    print("showInputImage     ",time_10) 

    counter=counter+1

    print("\nCunter", counter)
    
    end_time=time.time()

    timeInterval=end_time-start_time

    if timeInterval >=10:
        print("End.")
        break

    #Exit program when key "ESC" is pressed
    key = cv2.waitKey(1)
    if key == 27:
       break

cv2.destroyAllWindows()

 