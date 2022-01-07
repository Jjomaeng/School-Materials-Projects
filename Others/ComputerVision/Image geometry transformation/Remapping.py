# 삼각함수를 이용한 리매핑
# 주요 기능 : 리맵핑

import sys
import numpy as np
import cv2

src = cv2.imread('./data/tekapo.bmp')

if src is None :
    print("Image load failed")
    sys.exit()

h ,w = src.shape[:2]

map2,map1 = np.indices((h,w),dtype = np.float32) # 행에서 1씩 증가한 배열, 열에서 1씩 증가한 배열
map2 = map2 + 10 * np.sin(map1/32) #사인함수를 이용하여 왜곡

dst = cv2.remap(src,map1,map2,cv2.INTER_CUBIC,borderMode=cv2.BORDER_DEFAULT) #리맵핑

cv2.imshow('src',src)
cv2.imshow('dst',dst)
cv2.waitKey()
cv2.destroyAllWindows()