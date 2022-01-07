# 기준점 지정/미지정하여 이미지 회전하기
# 주요 기능 : 이미지 회전
# 특징 : 기준점 미지정하면 (0,0)이 default

import cv2
import sys
import numpy as np
import math

src = cv2.imread('./data/tekapo.bmp')

if src is None :
    print("image load failed")
    sys.exit()
#(0,0)기준 회전
rad = 20 * math.pi/180
aff = np.array([[math.cos(rad),math.sin(rad),0],\
    [-math.sin(rad),math.cos(rad),0]],dtype= np.float32)

dst = cv2.warpAffine(src,aff,(0,0)) # 회전 기준점을 제시하지 않을 때는 사용가능

#중심점 기준 회전
cp = (src.shape[1]/2,src.shape[0]/2) #항상 순서 주의!!!!
rot = cv2.getRotationMatrix2D(cp,20,0.5) #cp점을 기준으로 20도 회전 이미지 0.5로 줄이기

dst2 = cv2.warpAffine(src,rot,(0,0))


cv2.imshow('src',src)
cv2.imshow('dst',dst)
cv2.imshow('dst2',dst2)
cv2.waitKey()
cv2.destroyAllWindows()