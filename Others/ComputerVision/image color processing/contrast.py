# 이미지 명암비 조절
# 주요 기능 : 기본 명암비 조절, 히스토그램 스트레칭
# 특징 : 채도가 전 구간에 걸쳐 나오도록 변형하는 선형 변환 기법

import sys
import numpy as np
import matplotlib.pyplot as plt
import cv2

src = cv2.imread(".//data//lenna.bmp",cv2.IMREAD_GRAYSCALE)

if src is None:
    print("Image load failed")
    sys.exit()

alpha = 1.0
dst = np.clip((1+alpha)*src - 128*alpha,0,255) #채도를 높여주는건 덧셈, 명암비 조절은 곱셈
                                               #뺄셈을 하는 이유 : 너무 밝아서
dst2 = cv2.normalize(src,None,0,255,cv2.NORM_MINMAX) 
cv2.imshow("src",src)
cv2.imshow("dst",dst)
cv2.imshow('dst2',dst2)
cv2.waitKey()

hist = cv2.calcHist([dst2],[0],None,[256],[0,256])
org_hist = cv2.calcHist([src],[0],None,[256],[0,256])
plt.plot(org_hist)
plt.plot(hist)
plt.show()


cv2.destroyAllWindows()