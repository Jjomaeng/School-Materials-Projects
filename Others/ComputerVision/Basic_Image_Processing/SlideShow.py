# 이미지 파일 한번에 불러와서 슬라이드쇼 만들기
# 주요 기능 : 이미지 파일 한번에 처리


import glob
import sys
import cv2

img_files = glob.glob(".//images//*.jpg") #이미지 파일을 한번에 불러올때는 glob 사용 #리스트로 받아옴

if not img_files: #예외 처리 반드시 하기
    print("There are no jpg files")
    sys.exit()


cv2.namedWindow("SlideShow",cv2.WINDOW_NORMAL)
cv2.setWindowProperty("SlideShow",cv2.WND_PROP_FULLSCREEN,cv2.WINDOW_FULLSCREEN) # 화면에 꽉 차게 이미지 출력

cnt = len(img_files)
idx = 0

while True :
    img = cv2.imread(img_files[idx])

    if img is None :
        print("Image load failed")
        break

    cv2.imshow("SlideShow",img)

    if cv2.waitKey(1000) == 27:
        break

    idx += 1

    if idx >= cnt:
        idx = 0

cv2.destroyAllWindows()





