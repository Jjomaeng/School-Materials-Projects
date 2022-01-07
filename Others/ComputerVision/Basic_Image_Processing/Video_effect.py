# 동영상 전환 이펙트(페이드-인,페이드-아웃,디졸브,밀기,확대) 구현
# 주요 기능 : 동영상 전환

import cv2
import sys
import numpy as np

cap1 = cv2.VideoCapture(".//data//video1.mp4")
cap2 = cv2.VideoCapture(".//data//video2.mp4")

if not cap1.isOpened() or not cap2.isOpened():
    print("video open failed")
    sys.exit()

frame_cnt1 = int(cap1.get(cv2.CAP_PROP_FRAME_COUNT))
frame_cnt2 = int(cap2.get(cv2.CAP_PROP_FRAME_COUNT))
fps = cap1.get(cv2.CAP_PROP_FPS) # 24 # 초 당 24프레임이 보여짐
effect_frame = int(fps * 2) # effect frame은 48를 가짐

delay = int(1000/fps) # 두 프레임간의 시간 간격 #클수록 느려짐

w = round(cap1.get(cv2.CAP_PROP_FRAME_WIDTH))
h = round(cap1.get(cv2.CAP_PROP_FRAME_HEIGHT))
fourcc = cv2.VideoWriter_fourcc(*"DIVX")

out = cv2.VideoWriter(".//output//video_effect.avi",fourcc,fps,(w,h))

for i in range(frame_cnt1 - effect_frame) : # 첫번째 영상에서 2초 정도 남겨두기
    ret1,frame1 = cap1.read()

    if not ret1:
        print("video1 open failed")
        break

    out.write(frame1)

    cv2.imshow('frame',frame1)
    if cv2.waitKey(delay) == 27:
        break

#동영상 이펙트 전환
for i in range(effect_frame): # 2초동안 발생
    ret1,frame1 = cap1.read()
    ret2,frame2 = cap2.read()

    dx = int(w * i/ effect_frame) #잘라내는 위치

    #커튼 치듯이 옆으로
    #frame = np.zeros((h,w,3),dtype = np.uint8)
    #frame[:,0:dx] = frame2[:,0:dx]
    #frame[:,dx:w] = frame1[:,dx:w]

    #디졸브
    alpha = 1.0 - i/effect_frame
    frame = cv2.addWeighted(frame1,alpha,frame2,1-alpha,0)

    out.write(frame)
    cv2.imshow("frame",frame)
    cv2.waitKey(delay)

for i in range(frame_cnt2):
    ret2,frame2 = cap2.read()

    if not ret2:
        break

    out.write(frame2)

    cv2.imshow('frame',frame2)
    if cv2.waitKey(delay) == 27:
        break

cap1.release()
cap2.release()
out.release()
cv2.destroyAllWindows()


