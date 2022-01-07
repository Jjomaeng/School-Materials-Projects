# 동영상 크로마키
# 주요 기능 : 크로마키
# 특징 : 스페이스바를 이용하여 크로마키 조절

import sys
import cv2
import numpy as np

#크로마키 영상
cap1 = cv2.VideoCapture('.//data/woman.mp4')

if not cap1.isOpened():
    print("video open failed")
    sys.exit()

#배경
cap2 = cv2.VideoCapture(".//data//raining.mp4")

if not cap2.isOpened() :
    print("back_video open failed")
    sys.exit()

#두 동영상의 크기,fps는 같다고 가정
frame_cnt1 = round(cap1.get(cv2.CAP_PROP_FRAME_COUNT))
frame_cnt2 = round(cap2.get(cv2.CAP_PROP_FRAME_COUNT))
print('frame_cnt1 : ',frame_cnt1)
print('frame_cnt2 : ',frame_cnt2)

fps = cap1.get(cv2.CAP_PROP_FPS)
delay = int(1000/fps)

do_composit = False

while True :
    ret1,frame1 = cap1.read()

    if not ret1:
        break
    if do_composit:
        ret2,frame2 = cap2.read()

        if not ret2:
            break

        hsv = cv2.cvtColor(frame1,cv2.COLOR_BGR2HSV)
        mask = cv2.inRange(hsv,(50,150,0),(70,255,255))
        cv2.copyTo(frame2,mask,frame1)

    cv2.imshow('frame',frame1)
    key = cv2.waitKey(delay)

    if key == ord(' '):
        do_composit = not do_composit
    elif key == 27:
        break

cap1.release()
cap2.release()
cv2.destroyAllWindows()  