# 영상에 어파인 변환 함수 적용
# 주요 기능 : 행렬곱을 통한 영상 이동, 영상 평행사변형화

import sys
import numpy as np
import cv2

src = cv2.imread("./data/tekapo.bmp")

if src is None:
    print('Image load failed')
    sys.exit()

aff1 = np.array([[1,0,100],\
                [0,1,100]],dtype = np.float32) # 영상 이동하기

aff2 = np.array([[1,0.5,0],\
                [0,1,0]],dtype = np.float32) # 영상 평행사변형화


h,w = src.shape[:2]

dst1 = cv2.warpAffine(src,aff1,(0,0)) #영상에 행렬 적용 함수 #(0,0)이면 src와 같은 크기로 설정
                                          # 마지막은 영상 사이즈가 아니라 윈도우 사이즈 결정 
dst2 = cv2.warpAffine(src,aff2,(w+int(h*0.5),h))
 
cv2.imshow('src',src)
cv2.imshow('dst',dst1)
cv2.imshow('dst2',dst2)
cv2.waitKey()
cv2.destroyAllWindows()