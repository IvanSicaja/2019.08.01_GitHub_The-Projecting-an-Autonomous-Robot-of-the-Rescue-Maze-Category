import cv2 
import pytesseract as tess       #Libary for character recognition
from picamera.array import PiRGBArray
from picamera import PiCamera
import time
import numpy as np               #Libary for matrix processing

# Adding custom options for tesseract configuration
custom_config = r'--oem 3 --psm 6'

camera = PiCamera()
camera.resolution = (640, 480)
camera.framerate = 60
rawCapture = PiRGBArray(camera, size=(640, 480))

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




#################################################### MAIN LOOP #################################

for frame in camera.capture_continuous(rawCapture, format="bgr", use_video_port=False,burst=False):
   
    start_time=time.time()
    image = frame.array
    cv2.imshow("Frame", image)
    key = cv2.waitKey(1) & 0xFF
    picture_taken_time=time.time()
    print('Spended time for taking picture', picture_taken_time-start_time)
    
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
    print('Character which is recognised is: "',text,'"')
    
    rawCapture.truncate(0)
    end_time=time.time()
    print('Spended time for tesseract', end_time-picture_taken_time)
    
    #Exit program when key "ESC" is pressed
    key = cv2.waitKey(1)
    if key == 27:
       break

cv2.destroyAllWindows()