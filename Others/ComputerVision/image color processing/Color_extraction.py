# 트랙바를 이용하여 특정 영역 색상 추출
# 주요 기능 : 특저 색상 영역 추출
# 특징 : HSV로 채널 변경하여 추출한다 - 원색을 찾고 싶을 때 이용
#     : Trackbar 이용할때 반드시 window name 일치시키기

import sys
import numpy as np
import cv2

src = cv2.imread('.//data//candies.png')

if src is None :
    print("image load failed")
    sys.exit()

src_hsv = cv2.cvtColor(src,cv2.COLOR_BGR2HSV)

def on_trackbar(pos):

    #트랙바 위치 받기
    hmin = cv2.getTrackbarPos('H_min','color_extraction') 
    hmax = cv2.getTrackbarPos('H_max','color_extraction')

    # 특정 범위 안에 있는 행렬 원소 검출
    dst = cv2.inRange(src_hsv,(hmin,150,0),(hmax,255,255))
    cv2.imshow('color_extraction',dst)

cv2.imshow('src',src)
cv2.namedWindow('color_extraction')

cv2.createTrackbar('H_min','color_extraction',50,179,on_trackbar)
cv2.createTrackbar("H_max","color_extraction",80,179,on_trackbar)
on_trackbar(0) #pos 0에서 시작

cv2.waitKey()

cv2.destroyAllWindows()