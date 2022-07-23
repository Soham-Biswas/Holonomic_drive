#!/usr/bin/env python

# Import required modules
from encodings import utf_8
import time
import numpy as np
import serial
#import RPi.GPIO as GPIO

def calculate_u(x,y,z):
    matA= [[x],[y],[z]]
    matB = [[-0.33, 0.58, 0.33], [-0.33, -0.58, 0.33], [0.67, 0, 0.33]]
    return np.dot(matB,matA)


USB_PORT_1 = "/dev/ttyUSB0"
USB_PORT_2 = "/dev/ttyUSB1"



try:
   usb_1 = serial.Serial(USB_PORT_1, 9600, timeout=2)
   usb_2 = serial.Serial(USB_PORT_2, 115200, timeout=2)
except:
   print("ERROR - Could not open USB serial port.  Please check your port name and permissions.")
   print("Exiting program.")
   exit()



while True:
    x,y,z = (input("Enter: x y w:").split()) 
    x_vel = float(x)
    y_vel = float(y)
    theta = float(z)
    u1_old = [[110],[110],[110]]
    u1 = [[0],[0],[0]]
    result = calculate_u(x_vel, y_vel, theta)   
    u1, u2, u3 = round(result[0][0], 5), round(result[1][0], 5), round(result[2][0],5)
    data_to_be_sent = str(u1)+' '+str(u2)+' '+ str(u3)
    print(data_to_be_sent)
    usb_1.write(bytes(data_to_be_sent,'utf_8'))
    usb_2.write(bytes(data_to_be_sent,'utf_8'))
    # line_1 = usb_1.readline()  # read input from Arduino
    # line_1 = line_1.decode()  # convert type from bytes to string
    # print('Line 1', line_1)
    # line_2 = usb_2.readline()  # read input from Arduino
    # line_2 = line_2.decode()  # convert type from bytes to string
    # print('Line 2', line_2)