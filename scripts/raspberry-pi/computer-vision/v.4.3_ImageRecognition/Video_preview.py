import cv2
cap = cv2.VideoCapture(0)

while True:
    _, img = cap.read()
    cv2.imshow("slika", img)
    if cv2.waitKey(5) != -1:
        break
cap.release()
cv2.destroyAllWindows()