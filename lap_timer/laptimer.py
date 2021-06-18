import time
import datetime
import cv2
import numpy as np

n = 2000 # 判定するピクセル数

# webcamera for windows
movie = cv2.VideoCapture(0)

before = None
fps = int(movie.get(cv2.CAP_PROP_FPS))

lap_start = 0
lap_time = 0
total_time_1 = 0
total_time_2 = 0
lap_time_x = 0
i = 0
key = 0
date = 0

date = datetime.datetime.now()
f = open('laptime.csv', 'a', encoding='UTF-8')
datalist_1 = [str(date),"\n"]
f.writelines(datalist_1)
datalist_2 = ["lap, lap_time, total_time",'\n']
f.writelines(datalist_2)
f.close()

while True:
    print("「Enter」を押して計測を開始")
    key = input()
    if key == '':
        break

initial_time = time.time()

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
    # cv2.imshow("frame", frame)

    pixel_sum = np.sum(contours)
    white_pixel_number = pixel_sum/255

    if white_pixel_number > n:
        total_time_1 = time.time() - initial_time
        lap_time = total_time_1 - total_time_2
        total_time_2 = total_time_1

        if lap_time > 1:

            i = i + 1
            lap_time = lap_time + lap_time_x

            # ファイルへの書き込み
            f = open('laptime.csv', 'a', encoding='UTF-8')
            datalist = [str(i),",", str(lap_time),",", str(total_time_1),'\n']
            f.writelines(datalist)
            f.close()

            print()
            print("total_time", [i], "=", total_time_1)
            print("lap_time  ", [i], "=", lap_time)

            lap_time_x = 0            
            t = 0

        else:
            lap_time_x = lap_time

    elif cv2.waitKey(1) == 13:
        f = open('laptime.csv', 'a', encoding='UTF-8')
        f.write('\n')
        f.close()
        break

cv2.destroyAllWindows()  # ウィンドウを破棄