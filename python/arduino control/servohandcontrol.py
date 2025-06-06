import cv2
import mediapipe as mp
import time
import HandTrackingModule as htm
import keyboard
from pyfirmata import Arduino, SERVO, util

angle = 0
port = 'COM3'
pin = 10
board=Arduino(port)

board.digital[pin].mode=SERVO

board.digital[pin].write(0)

pTime = 0 
cTime = 0
cap = cv2.VideoCapture(0)   
detector = htm. handDetector()
    
while True:
    success, img = cap.read()
    img = detector.findHands(img)
    lmList = detector.findPosition(img,draw=False)
    if len(lmList) !=0:
        Landmarkpalm = lmList[0]
        if Landmarkpalm[2]<240:
#            board.digital[pin].write(0)
            if angle>0:
                angle = angle-5
                board.digital[pin].write(angle)
                #time.sleep(0.005)
        
        elif Landmarkpalm[2]>240:
#            board.digital[pin].write(180)
            if angle<180:
                angle = angle+5
                board.digital[pin].write(angle)
                #time.sleep(0.005)


    cTime = time.time()
    fps = 1/(cTime-pTime)
    pTime = cTime
        
    cv2.putText(img, str(int(fps)),(10,70), cv2.FONT_HERSHEY_SIMPLEX,1,(0,255,0),3)
        
    cv2.imshow('Image',img)
    cv2.waitKey(1)
    
    if keyboard.is_pressed('esc'):
        break
