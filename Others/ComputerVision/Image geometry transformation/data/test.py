import sys
import numpy as np
import cv2


def drawROI(img, corners):
    cpy = img.copy() # 복사본 만들기

    c1 = (192, 192, 255) #1번 컬러
    c2 = (128, 128, 255) #2번 컬러

    for pt in corners:
        cv2.circle(cpy, tuple(pt), 25, c1, -1, cv2.LINE_AA) #-1은 원의 내부를 채운다 

    cv2.line(cpy, tuple(corners[0]), tuple(corners[1]), c2, 2, cv2.LINE_AA) # 4개으 선 그리기 ,점들의 좌표는 튜플로 묶어야함
    cv2.line(cpy, tuple(corners[1]), tuple(corners[2]), c2, 2, cv2.LINE_AA)
    cv2.line(cpy, tuple(corners[2]), tuple(corners[3]), c2, 2, cv2.LINE_AA)
    cv2.line(cpy, tuple(corners[3]), tuple(corners[0]), c2, 2, cv2.LINE_AA)

    disp = cv2.addWeighted(img, 0.3, cpy, 0.7, 0) #두갱의 영상을 blend하는 형태로 출력하게( 이미지 둘 다 출력하게( 네모, 동그라미에 투명도가 들어감))
                                                  #속도가 느려지기 때문에 없어도 된다.
    return disp


def onMouse(event, x, y, flags, param): #mouse 콜백함수의 파라미터를 따라야함
    global srcQuad, dragSrc, ptOld, src

    if event == cv2.EVENT_LBUTTONDOWN: #마우스가 눌렸을때
        for i in range(4): #클릭한 부분의 모서리의 원 안에 들어갔는지 확인
            if cv2.norm(srcQuad[i] - (x, y)) < 25: # 반지름 보다 작은 지 확인
                dragSrc[i] = True #들어가있으면 드래그를 시작한다는 의미
                ptOld = (x, y) #드래그를 할때마다 원을 이동시키기 위해 마우스좌표를 저장
                break

    if event == cv2.EVENT_LBUTTONUP:
        for i in range(4):
            dragSrc[i] = False

    if event == cv2.EVENT_MOUSEMOVE: 
        for i in range(4):
            if dragSrc[i]: #마우스 왼쪽 버튼이 눌려있을 때에만
                dx = x - ptOld[0] #현재 점과 이전 점의 좌표의 변이 계산
                dy = y - ptOld[1]

                srcQuad[i] += (dx, dy) # 변이만큼 모서리 이동

                cpy = drawROI(src, srcQuad) #이동한 모서리 출력
                cv2.imshow('img', cpy)
                ptOld = (x, y)
                break


# 입력 이미지 불러오기
src = cv2.imread('./data/scanned.jpg')

if src is None:
    print('Image open failed!')
    sys.exit()

# 입력 영상 크기 및 출력 영상 크기
h, w = src.shape[:2]
dw = 500 #가로 크기 500픽셀로 규정
dh = round(dw * 297 / 210)  # A4 용지 크기: 210x297cm a4의 비율 곱하기

# 모서리 점들의 좌표, 드래그 상태 여부
srcQuad = np.array([[30, 30], [30, h-30], [w-30, h-30], [w-30, 30]], np.float32) #내가 선택하려는 모서리 점 4개를 저장할 ndarray #점은 임의로 초기화
dstQuad = np.array([[0, 0], [0, dh-1], [dw-1, dh-1], [dw-1, 0]], np.float32) #출력영상의 4개 점의 위치
dragSrc = [False, False, False, False] #4개의 점 중에서 어떤 점을 드래그 하고 있는 가를 저장하기 위한 리스트

# 모서리점, 사각형 그리기
disp = drawROI(src, srcQuad)

cv2.imshow('img', disp)
cv2.setMouseCallback('img', onMouse)

while True:
    key = cv2.waitKey()
    if key == 13:  # ENTER 키 #밑의 함수 실행
        break
    elif key == 27:  # ESC 키
        cv2.destroyWindow('img') #아예 창을 실행
        sys.exit()

# 투시 변환
pers = cv2.getPerspectiveTransform(srcQuad, dstQuad)
dst = cv2.warpPerspective(src, pers, (dw, dh), flags=cv2.INTER_CUBIC) #dw,dh는 결과영상의 크기

# 결과 영상 출력
cv2.imshow('dst', dst)
cv2.waitKey()
cv2.destroyAllWindows()