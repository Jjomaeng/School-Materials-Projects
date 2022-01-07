# 히스토그램 역투영을 통하여 같은 색상 찾기
# 주요 기능 : 히스토그램 역투영 , ROI 선택
# 특징 : YCrCb -> Y: 밝기 , Cr,Cb : 색상

import sys
import numpy as np
import cv2

src = cv2.imread(".//data//cropland.png")

if src is None:
    print("imgae load failed")
    sys.exit()

#영역 선택
x,y,w,h = cv2.selectROI(src)
src_ycrcb = cv2.cvtColor(src,cv2.COLOR_BGR2YCrCb)
crop = src_ycrcb[y:y+h,x:x+w]

#선택한 영역의 histogram 계산
channels = [1,2]
cr_bins = 128
cb_bins = 128
histSize = [cr_bins,cb_bins]
cr_range = [0,256]
cb_range = [0,256]
ranges = cr_range + cb_range # 출력값 : [0,256,0,256]
print(ranges)

hist = cv2.calcHist([crop],channels,None,histSize,ranges)
hist_norm = cv2.normalize(cv2.log(hist+1),None,0,255,cv2.NORM_MINMAX,cv2.CV_8U)

#역투영
backproj = cv2.calcBackProject([src_ycrcb],channels,hist,ranges,1) # 같은 색상의 마스크를 반환

dst = cv2.copyTo(src,backproj) #여기서 backproj가 마스크

cv2.imshow("backprojection",backproj)
cv2.imshow("hist_norm",hist_norm)
cv2.imshow('dst',dst)
cv2.waitKey()
cv2.destroyAllWindows()