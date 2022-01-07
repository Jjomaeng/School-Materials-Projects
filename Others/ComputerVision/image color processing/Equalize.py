# 흑백과 컬러 영상의 히스토그램 평활화
# 주요 기능 : 히스토그램 평활화
# 특징 : 컬러 영상은 밝기 부분만 평활화가 이루어져야 한다. -> YCRCB

import sys
import numpy as np
import cv2

#흑백
src = cv2.imread(".//data//input.jpg",cv2.IMREAD_GRAYSCALE)

if src is None:
    print("image is failed")
    sys.exit()

dst = cv2.equalizeHist(src)

cv2.imshow('src',src)
cv2.imshow('dst',dst)
cv2.waitKey()

cv2.destroyAllWindows()

src = cv2.imread(".//data//input.jpg")

if src is None :
    print("Image load failed")
    sys.exit()

src_ycrcb = cv2.cvtColor(src,cv2.COLOR_BGR2YCrCb)
ycrcb_planes = cv2.split(src_ycrcb)

ycrcb_planes[0] = cv2.equalizeHist(ycrcb_planes[0])

dst_ycrcb = cv2.merge(ycrcb_planes)
dst = cv2.cvtColor(dst_ycrcb,cv2.COLOR_YCrCb2BGR)

cv2.imshow('src',src)
cv2.imshow('equalize',dst)
cv2.waitKey()

cv2.destroyAllWindows()

