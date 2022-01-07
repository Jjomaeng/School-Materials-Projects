# 가우시안 필터를 사용하여 blurring
# 주요 기능 : 가우시안 필터
# 특징 : MeanFilter 보다 quality가 좋음
#     : 시그마를 조절하여 blurring 조절

import sys
import numpy as np
import cv2

src = cv2.imread('.//data//rose.bmp',cv2.IMREAD_GRAYSCALE)

if src is None :
    print("Image load failed")
    sys.exit()

cv2.imshow('srcs',src)

for sigma in range(1,6):

    dst = cv2.GaussianBlur(src,(0,0),sigma) #커널 사이즈를 직접 주지않고 시그마에 의해 자동 결정 되도록
    desc = 'sigma = {}'.format(sigma)
    cv2.putText(dst,desc,(10,30),cv2.FONT_HERSHEY_SIMPLEX,1.0,255,1,cv2.LINE_AA)

    cv2.imshow('dst',dst)
    cv2.waitKey()

cv2.destroyAllWindows()

