# MedianFilter를 이용하여 잡음 제거
# 주요 기능 : 잡음제거
# 특징 : Salt & Pepper noise 제거에 효과적

import sys
import cv2
import numpy as np

src = cv2.imread('./data/noise.bmp',cv2.IMREAD_GRAYSCALE)

if src is None :
    print('imgae load failed')
    sys.exit()

dst = cv2.medianBlur(src,3)

cv2.imshow('src',src)
cv2.imshow('dst',dst)
cv2.waitKey()

cv2.destroyAllWindows()