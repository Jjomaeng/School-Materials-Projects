# img1에서 찾은 색상을 img2에서 찾고 싶을 때
# 주요 기능 : 역투영 , 마스크를 이용한 ROI
# 특징 : 두가지 이미지 사용

import sys
import numpy as np
import cv2

ref = cv2.imread('.//data//kids1.png',cv2.IMREAD_COLOR)
mask = cv2.imread(".//data//kids1_mask.bmp",cv2.IMREAD_GRAYSCALE)

if ref is None or mask is None:
    print("image load failed")
    sys.exit()
# 참조영상에서 마스크를 이용한 색상 histogram 계산
ref_ycrcb = cv2.cvtColor(ref,cv2.COLOR_BGR2YCrCb)
channels = [1,2]
ranges = [0,256,0,256]

#채널 참고 : gray는 [0], 컬러는 [,,] 이렇게 입력해야한다. 하지만 ycrcb에서 [0]은 사용하지 않는다
hist = cv2.calcHist([ref_ycrcb],channels,mask,[128,128],ranges)
hist_norm = cv2.normalize(cv2.log(hist+1),None,0,255,cv2.NORM_MINMAX,cv2.CV_8U)

#영상에서 색상 찾기
src = cv2.imread(".//data//kids2.png",cv2.IMREAD_COLOR)

if src is None :
    print("src load failed")
    sys.exit()

src_ycrcb = cv2.cvtColor(src,cv2.COLOR_BGR2YCrCb)

backproj = cv2.calcBackProject([src_ycrcb],channels,hist,ranges,1)
dst = cv2.copyTo(src,backproj)

cv2.imshow('src',src)
cv2.imshow('hist_norm',hist_norm)
cv2.imshow('backproj',backproj)
cv2.imshow('dst',dst)

cv2.waitKey()
cv2.destroyAllWindows()


