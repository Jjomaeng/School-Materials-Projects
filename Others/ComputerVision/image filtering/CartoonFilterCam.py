# 실시간 웹캠에 여러가지 필터 적용하기
# 주요 기능 : 카툰 필터, 연필 스케치 필터

import sys
import numpy as np
import cv2

#cartoon 필터 함수
def cartoon_filter(img):
    h,w = img.shape[:2]
    img2 = cv2.resize(img,(w//2,h//2))

    blr = cv2.bilateralFilter(img2,-1,3,3)
    edge = 255 - cv2.Canny(img2,80,120) # 외곽선 추출
    edge = cv2.cvtColor(edge,cv2.COLOR_GRAY2BGR)

    dst = cv2.bitwise_and(blr,edge)
    dst = cv2.resize(dst,(w,h),interpolation=cv2.INTER_NEAREST)

    return dst

def pencil_sketch(img):
    gray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
    blr = cv2.GaussianBlur(gray,(0,0),10)
    dst = cv2.divide(gray,blr,scale = 255)

    return dst

cap = cv2.VideoCapture(0)

if not cap.isOpened():
    print('video open failed')
    sys.exit()

cam_mode = 0

while True :
    ret,frame = cap.read()

    if not ret:
        break
    
    if cam_mode == 1:
        frame = cartoon_filter(frame)
    elif cam_mode == 2:
        frame = pencil_sketch(frame)
        frame = cv2.cvtColor(frame,cv2.COLOR_GRAY2BGR)
        

    cv2. imshow("filtering",frame)
    key = cv2.waitKey(1)

    if key == 27:
        break
    elif key == ord(' '):
        cam_mode += 1
        if cam_mode == 3:
            cam_mode = 0


cap.relese()
cv2.destroyAllWindows()
