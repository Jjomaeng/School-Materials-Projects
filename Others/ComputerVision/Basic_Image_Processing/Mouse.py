#마우스로 그림 그리기
#주요 기능 : 마우스 이벤트 처리
#특징 : CallBack함수 사용

import cv2
import sys
import numpy as np
import random

oldx = oldy = -1 #이전 좌표와 연결하기 위함
drawing = False

#마우스 콜백함수
def on_mouse(event,x,y,flags,param):
    global img,oldx,oldy,drawing

    if event == cv2.EVENT_LBUTTONDOWN:
        oldx, oldy = x,y
    elif event == cv2.EVENT_MOUSEMOVE: #마우스 버튼이 눌린 채로 움직일 때만 작동하게
        if flags & cv2.EVENT_FLAG_LBUTTON :
            r = 255
            b = 0
            g = 0

            cv2.line(img,(oldx,oldy),(x,y),(b,g,r),5,cv2.LINE_AA)
            cv2.imshow("drawing",img)
            oldx,oldy = x,y
img = np.ones((640,640,3),dtype = np.uint8) * 255 #하얀색 배경 만들기

cv2.namedWindow("drawing")
cv2.setMouseCallback("drawing",on_mouse)# callback함수 지정
cv2.imshow('drawing',img)
cv2.waitKey()

cv2.destroyAllWindows()

