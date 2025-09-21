import cv2 
import pytesseract as tess       #Libary for character recognition
from picamera.array import PiRGBArray
from picamera import PiCamera
import time
import numpy as np               #Libary for matrix processing
from PIL import Image
import serial
import RPi.GPIO as GPIO


###################################### Buzzer pin Setup ######################################

#Disable warnings (optional)
GPIO.setwarnings(False)
#Select GPIO mode
GPIO.setmode(GPIO.BCM)
#Set buzzer - pin 21 as output
buzzerPin=21 
GPIO.setup(buzzerPin,GPIO.OUT)

##############################################################################################
###################################### Blink LED pin Setup ######################################
 
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
LEDPin=16
GPIO.setup(LEDPin,GPIO.OUT)

##############################################################################################
###################################### Push Elektromotor pin Setup ######################################
 
ElectroMotor_PIN1=26
ElectroMotor_PIN2=19
 

#Disable warnings (optional)
GPIO.setwarnings(False)
#Select GPIO mode
GPIO.setmode(GPIO.BCM)
#Set buzzer - pin 23 as output
GPIO.setup(ElectroMotor_PIN1,GPIO.OUT)
#Run forever loop

#Disable warnings (optional)
GPIO.setwarnings(False)
#Select GPIO mode
GPIO.setmode(GPIO.BCM)
#Set buzzer - pin 23 as output
GPIO.setup(ElectroMotor_PIN2,GPIO.OUT)

##############################################################################################

# Adding custom options for tesseract configuration
custom_config = r'--oem 3 --psm 6'

camera = PiCamera()
camera.resolution = (640, 480)
camera.framerate = 60
rawCapture = PiRGBArray(camera, size=(640, 480))

###################################### Push Box function ######################################

def pushBox(PIN1,PIN2,boxes_amount,delay):
    
    time_1=time.time()
    time_2=time.time()
    boxCounter=0
    
    while boxCounter<boxes_amount:
        boxCounter=boxCounter+1
        time_2=time.time()
        
        time_3=time.time()
        time_4=time.time()
        
        while((time_4-time_3)<(0.1)):
            GPIO.output(PIN1,GPIO.LOW)
            GPIO.output(PIN2,GPIO.HIGH)
            time_4=time.time()
            
        time_3=time.time()
        time_4=time.time()
        
        while((time_4-time_3)<(delay)):
            GPIO.output(PIN1,GPIO.LOW)
            GPIO.output(PIN2,GPIO.LOW)
            time_4=time.time()

###################################### Buzzer and LED blink function ######################################
 
def on_off_in_time_interval(buzzer_pin,LED_pin,duration_interval_in_secnods,delay_time):
    
    time_1=time.time()
    time_2=time.time()
    
    while((time_2-time_1)<(duration_interval_in_secnods)):
        
        time_2=time.time()
        
        time_3=time.time()
        time_4=time.time()
        
        while((time_4-time_3)<(delay_time)):
            GPIO.output(buzzer_pin,GPIO.HIGH)
            GPIO.output(LED_pin,GPIO.HIGH)
            time_4=time.time()
            
        time_3=time.time()
        time_4=time.time()
        
        while((time_4-time_3)<(delay_time)):
            GPIO.output(buzzer_pin,GPIO.LOW)
            GPIO.output(LED_pin,GPIO.LOW)
            time_4=time.time()
            


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

def showAndWaitEscKey(header, image):
    cv2.imshow(header,image )
    k = cv2.waitKey(0)
    if k == 27:         # wait for ESC key to exit
       cv2.destroyAllWindows()

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
    
    print("Recognised color is Green with ",round(numberOfGreenPixelPercent,2),"%")

def showInputImage(frame):
    
    cv2.imshow("Ulazna slika", frame)
    #cv2.imshow("Konacna slika", finall_Image)


########################################### PROGRAM START HERE - MAIN LOOP #################################
#ser = serial.Serial('/dev/ttyACM0', 9600)
#ser.flush()



for frame in camera.capture_continuous(rawCapture, format="bgr", use_video_port=False,burst=False):

    start_time=time.time()
    image = frame.array
    imageForColorRecognition = frame.array
    # Prikaz kamere
    cv2.imshow("Frame", image)
    key = cv2.waitKey(1) & 0xFF
    picture_taken_time=time.time()
    print('Spended time for taking picture', picture_taken_time-start_time)
    
    
    ############################ Color Recognition ##########################
    
    
    #Convert image color values to HSV format
    hsv = cv2.cvtColor(imageForColorRecognition, cv2.COLOR_BGR2HSV)
    #time_1=time.time()
    #print("convertToHSV       ",time_1)
    imageForColorRecognition = Image.fromarray(imageForColorRecognition)

    pixelCounter(imageForColorRecognition)
    #time_1=time.time()
    #print("pixelCounter       ",time_1)  

    redColorFilter(hsv,imageForColorRecognition)
    #time_1=time.time() 
    #print("redColorFilter     ",time_1)  

    orangeColorFilter(hsv,imageForColorRecognition)
    #time_1=time.time() 
    #print("orangeColorFilter  ",time_1) 

    greenColorFilter(hsv,imageForColorRecognition)
    #time_1=time.time() 
    #print("greenColorFilter   ",time_1)
    
   
    ######################### Character Recognition #########################
    
    #Preprocessing
    gray = get_grayscale(image)
    #showAndWaitEscKey("Grayscaled image", gray)
        
    thresh = thresholding(gray)
    #showAndWaitEscKey('Theresholded image',thresh  )
        
    openFilter = opening(thresh)
    #showAndWaitEscKey('Opening image',openFilter )
        
    #Extracting charcter from image
    text = tess.image_to_string(openFilter, config=custom_config)
    #Print founded chharacter
    #print('Characters which is recognised is: "',text,'"')
    lenght=len(text)
    #print('Lenght of text is: ',lenght)
    
    if lenght<3:
        #print('Nalazimo se u petlji.' )
        H=text.find('H',0,2)
        S=text.find('S',0,2)
        U=text.find('U',0,2)
        
        if H==0 or H==1:
            # Slanje texta ""Hello from Raspberry Pi!" na Arduino
            #ser.write(b'HFND!\n')
            print('H character recognised: ', H )
            
        if S==0 or S==1:
            # Slanje texta ""Hello from Raspberry Pi!" na Arduino
            #ser.write(b'SFND\n')
            print('S character recognised: ', S )
            on_off_in_time_interval(buzzerPin,LEDPin,5,0.125)
            pushBox(ElectroMotor_PIN1,ElectroMotor_PIN2,2,1)
        
        if U==0 or U==1:
            # Slanje texta ""Hello from Raspberry Pi!" na Arduino
            #ser.write(b'UFND\n')
            print('U character recognised: ', U )
            
    
    
    rawCapture.truncate(0)
    end_time=time.time()
    print('Spended time for tesseract', end_time-picture_taken_time)
    print(' ' )
    
    #Exit program when key "ESC" is pressed
    key = cv2.waitKey(1)
    if key == 27:
       break

cv2.destroyAllWindows()
