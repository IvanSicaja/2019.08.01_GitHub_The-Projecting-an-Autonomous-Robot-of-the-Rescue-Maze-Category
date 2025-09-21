#Including needed libraries

from tkinter import *      #Libary for Tkinter form PC-events

import tkinter as tkr      #Libary for Tkinter form PC-events
import PIL as p            #Python Image Library
import PIL.ImageTk as ptk  #Python Image Library subdirectory specified for Tkinter library
import pyautogui as pg     #Libary for gloabl PC-events
import cv2                 #Libary for image processing
import math                #Library for math operations
from PIL import Image      #Python Image Library subdirectory

def rgb2hsv(r, g, b):
    r, g, b = r/255.0, g/255.0, b/255.0
    mx = max(r, g, b)
    mn = min(r, g, b)
    df = mx-mn
    if mx == mn:
        h = 0
    elif mx == r:
        h = (60 * ((g-b)/df) + 360) % 360
    elif mx == g:
        h = (60 * ((b-r)/df) + 120) % 360
    elif mx == b:
        h = (60 * ((r-g)/df) + 240) % 360
    if mx == 0:
        s = 0
    else:
        s = df/mx
    v = mx

    hScaled=h/1.411764706
    sScaled=s*255
    vScaled=v*255

    print("HSV   ",round(h,1)," ",round(s,3)," ",round(v,3))
    print("HSV_C ",round(hScaled,1)," ",round(sScaled,1)," ",round(vScaled,1))
    return hScaled, sScaled, vScaled

#Function which on left mouse click returns HSV pixel values 
def leftClick(event):
    posXY=pg.position() 
    RGB= pg.pixel(posXY[0],posXY[1])                                        #Current mouse position
    R=RGB[0]
    G=RGB[1]
    B=RGB[2]
    print("\n") 
    print("RGB   ",R," ",G," ",B)
     
   
    rgb2hsv(R,G,B)
      #Clicked pixel HSV values

 
window=tkr.Tk()                     #Open Tkinter window
window.title("Find HSV values")     #Change title of Tkinter window

pic='colorImg.png'                #Include image (reletive adressing)
pic1=p.Image.open(pic)              #Open image
width, height=pic1.size             #Opend image dimension
imgSize=str(width)+"x"+str(height)
print("Width  ",width)
print("Height ",height)
window.geometry(imgSize)            #Specifier size of Tkinter window
photo=ptk.PhotoImage(pic1)          #Open image in Tkinter window 

label1=tkr.Label(window,image=photo) #Put image to Tkinter container
label1.bind("<Button-1>",leftClick)  #Call 'leftClick' function
label1.pack()                        #Pack image to Tkinter label
window.mainloop()                    #Loop Tkinter window 

 
    
 
     
 

    
 
 
