#양방향 필터를 이용하여 가우시안 잡음 제거하기
# 주요 기능 : 양방향 필터
# 특징 : 가우시안 잡음은 가우시안 필터로 제거하는 것이 효과적이지만 edge의 마모가 심함
#     : 거리와 색상에 대한 가중치를 두는 양뱡향 필터가 효과적
#     : 계산 속도가 느림

import sys
import cv2
import numpy as np

src = cv2.imread('.//data//lenna.bmp')

if src is None :
    print("Image load failed")
    sys.exit()

# 필터링에 사용될 이웃 픽셀의 거리(지름)은 simgaSpace에 의해 자동 결정 되도록 -1 지정
# 컬러에 대한 sigma = 10, 공간에 대한 sigma = 5
dst = cv2.bilateralFilter(src,-1,10,5)

cv2.imshow('src',src)
cv2.imshow('dst',dst)
cv2.waitKey()

cv2.destroyAllWindows()