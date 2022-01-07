#마스크 연산과 ROI
#주요 기능 : 배경에 원하는 부분의 그림을 잘라서 넣기
#          png 이미지를 이용한 로고 넣기

import cv2
import sys

src = cv2.imread(".//data//airplane.bmp",cv2.IMREAD_COLOR) # 넣을 이미지
mask = cv2.imread(".//data//mask_plane.bmp",cv2.IMREAD_GRAYSCALE) #자를 부분을 위한 mask
dst = cv2.imread(".//data//field.bmp",cv2.IMREAD_COLOR)
cat = cv2.imread(".//data//cat.bmp") #로고를 넣을 배경
logo = cv2.imread(".//data//opencv-logo-white.png",cv2.IMREAD_UNCHANGED) #png파일을 불러올때는 반드시 unchanged 속성!!

if src is None or mask is None or dst is None or cat is None or logo is None:
    print("image load failed")
    sys.exit()


mask_logo = logo[:,:,-1] #png의 마지막 채널은 흑백 영상(mask로 이용)
logo = logo[:,:,0:3] #나머지가 삼원색의 마스크 당할 이미지

h,w = logo.shape[:2]
crop = cat[0:h,0:w] #참조개념

cv2.copyTo(logo,mask_logo,crop) # 반드시 copy는 사이즈가 같아야 한다 그래서 crop을 만드는 이유
cv2.copyTo(src,mask,dst) # src에 있는 mask 부분을 dst에 copy하라

cv2.namedWindow("Mask and ROI")
cv2.imshow("Mask and ROI",dst) # 결국은 dst에 최종 결과물이 옮겨져 있음
cv2.namedWindow("LOGO ROI")
cv2.imshow("LOGO ROI",cat)

cv2.waitKey()

cv2.destroyAllWindows()

