import time
import cv2
import numpy as np

start = time.time()

# webcam for ubuntu
# movie = cv2.VideoCapture(2)

# webcamera for windows
movie = cv2.VideoCapture(1)

before = None
fps = int(movie.get(cv2.CAP_PROP_FPS))
time.sleep(1/fps)
ret, frame = movie.read()

lap_start = 0

while True:

    ret, frame = movie.read()
    if ret == False:
        break

    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    if before is None:
        before = gray.astype("float")
        continue

    cv2.accumulateWeighted(gray, before, 0.95)
    frameDelta = cv2.absdiff(gray, cv2.convertScaleAbs(before))

    thresh = cv2.threshold(frameDelta, 3, 255, cv2.THRESH_BINARY)[1]

    contours = cv2.findContours(
        thresh, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)[0]

    cv2.imshow("frame", contours)

    pixel_sum = np.sum(contours)
    white_pixel_number = pixel_sum/255
    # print(white_pixel_number)

    if white_pixel_number > 9000:
        total_time = time.time() - start
        lap_time = time.time() - lap_start
        lap_start = time.time()
        print(total_time)
        print(lap_time)

    elif cv2.waitKey(0) == 13:
        break

cv2.destroyAllWindows()  # ウィンドウを破棄
