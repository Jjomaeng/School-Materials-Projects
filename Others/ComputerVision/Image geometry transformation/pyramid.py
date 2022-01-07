# 피라미드 영상을 만들어 사각형 그리기
# 주요 기능 : 피라미드 영상(업샘플링/다운샘플링)

import sys
import cv2
import numpy as np

src = cv2.imread('./data/cat.bmp')

if src is None:
    print('image load failed')
    sys.exit()

rc = (250,120,200,200) # 고양이 얼굴 좌표 표시

cpy = src.copy()

cv2.rectangle(cpy,rc,(0,0,255),2)
cv2.imshow('src',cpy)
cv2.waitKey()

for i in range(1,4):
    src = cv2.pyrDown(src) # downsampling
    cpy = src.copy()
    cv2.rectangle(cpy,rc,(0,0,255),2,shift=i) #shift는 크기 조정 파라미터
    cv2.imshow('src',cpy) #윈도우 네임 formating으로 지정하니까 안된다,,,,왜일까
    cv2.waitKey()
    cv2.destroyWindow('src') #윈도우 지정해서 삭제할때

cv2.destroyWindow()