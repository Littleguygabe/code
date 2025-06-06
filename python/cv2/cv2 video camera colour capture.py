import cv2
import numpy as np
from mss import mss

lower = np.array([10,10,20])
upper = np.array([25,255,255])
#mon = {'left': 0, 'top': 0, 'width': 1920, 'height': 1080}

video = cv2.VideoCapture(0)
#video = mss().grab(mon)

while True:
    success, img = video.read()
    image = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)
    mask = cv2.inRange(image, lower, upper)

    contours, hierarchy = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    if len!=0:
        for contour in contours:
            if cv2.contourArea(contour) > 500:
                x, y, w, h = cv2.boundingRect(contour)
                cv2.rectangle(img, (x,y), (x+w, y+h), (0, 0, 255), 3)

    cv2.imshow('mask', mask)
    cv2.waitKey(1)

    cv2.imshow('webcam', img)
    cv2.waitKey(1)

    if cv2.waitKey(1) & 0xFF in (
            ord('x'), 
            27, 
        ):
            break