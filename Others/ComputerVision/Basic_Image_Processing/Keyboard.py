#키보드로 영상 반전시키기
#주요 기능 : 키보드 이벤트 처리
#특징 : CallBack 함수가 필요하지 않음

import sys
import cv2
import numpy as np

img = cv2.imread(".//data//cat.bmp",cv2.IMREAD_GRAYSCALE)

if img is None:
    print("img load failed")
    sys.exit()

cv2.imshow('imgae',img)

while True:
    keycode = cv2.waitKey() # waitkey로 다양한 값을 받으려면 변수에 저장해야한다.
    if keycode == ord('i') or keycode == ord('I') : #keyboard 이벤트 처리는 callBack없이 이벤트 처리로
        img = ~img
        cv2.imshow("keyboard_event",img)

    elif keycode == 27:
        break

cv2.destroyAllWindows()
    