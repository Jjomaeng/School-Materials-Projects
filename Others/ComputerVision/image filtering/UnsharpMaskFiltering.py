# 흑백 영상과 컬러 영상에 대하여 언샤프 마스크 필터
# 주요 기능 : 언샤프 마스크 필터(색채가 날카로운 영상 만들기)
# 특징 : 컬러 영상 ycrcb로 변환

import numpy as np
import cv2
import sys

#흑백 영상
src = cv2.imread(".//data//rose.bmp",cv2.IMREAD_GRAYSCALE)

if src is None:
    print("Image load failed")
    sys.exit()

blr = cv2.GaussianBlur(src,(0,0),2)
dst = np.clip(2.0 * src - blr,0,255).astype(np.uint8)
cv2.imshow('dst',dst)
cv2.waitKey()
cv2.destroyAllWindows()

#컬러 영상
src = cv2.imread(".//data//rose.bmp")

if src is None :
    print("color image load failed")
    sys.exit()

src_ycrcb = cv2.cvtColor(src,cv2.COLOR_BGR2YCrCb)

src_f = src_ycrcb[:,:,0].astype(np.float32) # 계산이 들어가기 때문에 float으로
blr = cv2.GaussianBlur(src_f,(0,0),2.0)
src_ycrcb[:,:,0] = np.clip(2.0 * src_f - blr,0,255).astype(np.uint8)

dst = cv2.cvtColor(src_ycrcb,cv2.COLOR_YCrCb2BGR)

cv2.imshow('src',src)
cv2.imshow('color_dst',dst)
cv2.waitKey()
cv2.destroyAllWindows()
