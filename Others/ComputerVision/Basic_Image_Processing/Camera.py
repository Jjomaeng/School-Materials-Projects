#실시간 카메라 영상 저장하기
#동영상 불러와서 반전시키기
#주요 기능 : 카메라 접근,저장,동영상 불러오기, 영상 반전

import sys
import cv2

video = cv2.VideoCapture(".//data//video1.mp4")
camera = cv2.VideoCapture(0)

if not video.isOpened() or not camera.isOpened():
    print("video open failed")
    sys.exit()

#비디오의 주요 속성 확인하기
print("Frame width : ",int(video.get(cv2.CAP_PROP_FRAME_WIDTH)))
print("Frame height : ",int(video.get(cv2.CAP_PROP_FRAME_HEIGHT)))
print("프레임 수 : ",int(video.get(cv2.CAP_PROP_FRAME_COUNT)))

fps1 = video.get(cv2.CAP_PROP_FPS)
delay1 = round(1000/fps1) #delay는 정수로 해야함 -> round하는 이유

#카메라 저장하기

w = round(camera.get(cv2.CAP_PROP_FRAME_WIDTH))
h = round(camera.get(cv2.CAP_PROP_FRAME_HEIGHT))
fps2 = camera.get(cv2.CAP_PROP_FPS)

fourcc = cv2.VideoWriter_fourcc(*"DIVX")
delay2 = round(1000/fps2)

out = cv2.VideoWriter(".//output//camera_output.avi",fourcc,fps2,(w,h))

#동영상 반전 시키기

while True:
    ret,frame = video.read()


    if not ret: #무한 루프 빠져나오기 위한 조건문
        break

    inverse = ~frame
    cv2.imshow("inversed video",inverse)

    if cv2.waitKey(delay1) == 27:
        break
#카메라 처리
while True:
    ret, frame = camera.read()

    if not ret:
        break

    out.write(frame)

    cv2.imshow("camera",frame)

    if cv2.waitKey(delay2) == 27:
        break

#항상 메모리 release 해주기
video.release()
camera.release()
out.release()
cv2.destroyAllWindows()





