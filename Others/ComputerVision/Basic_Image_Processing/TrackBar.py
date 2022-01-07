# 트랙바로 명암대비 조정하기
# 주요 기능 : 트랙바
# 특징 : 콜백 함수 사용 , 콜백함수 지정은 창 생성 밑에서 코드 실행해야함

import cv2
import sys
import numpy as np
from numpy.lib.type_check import imag

#트랙바 콜백함수

def on_trackbar(pos): #trackbar의 현재 위치를 pos로 받음
    global img #이미지는 항상 전역변수로 선언

    level = pos * 16 #pos의 단계 설정 ->16으로
    level = np.clip(level,0,255) #범위를 넘기면 0이나 255로 지정

    img[:,:] = level
    cv2.imshow("TrackBar",img)

img = np.zeros((480,640),np.uint8)

cv2.namedWindow("TrackBar")

cv2.createTrackbar('level',"TrackBar",0,16,on_trackbar) # 반드시 창 생성 코드 밑에서 실행해야한다
cv2.imshow("TrackBar",img)
cv2.waitKey()

cv2.destroyAllWindows()



