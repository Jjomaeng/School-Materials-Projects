# 이미지를 확대했을 경우 플래그에 따른 quality변화 확인하기
# 주요 기능 : 플래그별로 이미지 확대

import sys
import cv2
import numpy as np

src = cv2.imread('./data/rose.bmp')

if src is None :
    print('image load failed')
    sys.exit()
h,w = src.shape[:2]
dst1 = cv2.resize(src,(0,0),fx = 4,fy = 4,interpolation=cv2.INTER_NEAREST) #가장 quality가 떨어짐
dst2 = cv2.resize(src,(4*w,4*h)) # default는 inter_linear
dst3 = cv2.resize(src,(4*w,4*h),cv2.INTER_CUBIC)
dst4 = cv2.resize(src,(4*w,4*h),interpolation= cv2.INTER_LANCZOS4)

cv2.imshow('src',src)
cv2.imshow('inter_nearest',dst1[500:900,400:800])
cv2.imshow('inter_linear',dst2[500:900,400:800])
cv2.imshow('inter_cubic',dst3[500:900,400:800])
cv2.imshow('inter_lanczos',dst4[500:900,400:800])
cv2.waitKey()
cv2.destroyAllWindows()
