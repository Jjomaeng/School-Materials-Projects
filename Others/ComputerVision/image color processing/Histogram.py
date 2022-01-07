# 영상의 histogram 분석하기
# 주요 기능 : 흑백,컬러 영상의 histogram 분석하기
# 특징 : 컬러 이미지 같은 경우에는 채널을 분리해서 histogram을 그린다.
#     : Histogram을 그릴 수 있는 방법은 matplotlib과 opencv 함수 생성해서 그릴 수 있음 

import sys
import numpy as np
import matplotlib.pyplot as plt
import cv2

def getGrayHistImage(hist):
    imgHist = np.full((100,256),255,dtype = np.uint8)
    histMax = np.max(hist)

    for x in range(256):
        pt1 = (x,100)
        pt2 = (x,100 - int(hist[x,0]*100/histMax)) #100을 넘기지 않기 위해 # 차이를 그리기 위해
        print("pt1 : {} pt2 : {}".format(pt1,pt2))
        cv2.line(imgHist,pt1,pt2,0)

    return imgHist

src = cv2.imread('.//data//lenna.bmp',cv2.IMREAD_GRAYSCALE)

if src is None :
    print('Image load failed')
    sys.exit()

hist = cv2.calcHist([src],[0],None,[256],[0,256])
histImg = getGrayHistImage(hist)# hist 계산해서 넘겨주기

cv2.imshow('matplotlib_gray',src)
cv2.imshow('opencv_gray',histImg)
cv2.waitKey(1)

plt.plot(hist)
plt.show()

src2 = cv2.imread('.//data//lenna.bmp')

if src2 is None :
    print("Image load failed")
    sys.exit()

colors = ['b','g','r']
bgr_planes = cv2.split(src2)

for(p,c) in zip(bgr_planes,colors) : #zip 함수 : 튜플 형태로 반환 -> p,c가 각각 받음
    hist = cv2.calcHist([p],[0],None,[256],[0,256])
    plt.plot(hist,color = c)

cv2.imshow('color',src2)
cv2.waitKey(1)

plt.show()

cv2.destroyAllWindows()