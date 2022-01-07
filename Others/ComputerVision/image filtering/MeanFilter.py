# 평균값 필터를 이용하여 영상 blur 처리
# 주요기능 : 평균값 필터
# 특징 : 직접 필터 생성과 함수 사용하는 방법이 있음
#     : 커널이 커질수록 blur 효과가 커짐

import sys
import cv2
import numpy as np

src = cv2.imread('.//data//rose.bmp',cv2.IMREAD_GRAYSCALE)

if src is None :
    print("image load failed")
    sys.exit()

# 직접 커널 생성하기
kernel = np.ones((3,3),dtype = np.float64) / 9 #커널 생성
dst1 = cv2.filter2D(src,-1,kernel) #커널 적용

#함수로 적용
dst2 = cv2.blur(src,(3,3))

#커널 사이즈에 따른 blurring 효과 비교
for ksize in (3,5,7):
    dst = cv2.blur(src,(ksize,ksize))

    desc = "Mean : {}X{}".format(ksize,ksize)
    cv2.putText(dst,desc,(10,30),cv2.FONT_HERSHEY_SIMPLEX,1.0,255,1,cv2.LINE_AA)
    cv2.imshow('dst',dst)
    cv2.waitKey()

cv2.destroyAllWindows()
    

cv2.imshow('src',src)
cv2.imshow('dst',dst1)
cv2.imshow('dst2',dst2)

cv2.waitKey()

cv2.destroyAllWindows()