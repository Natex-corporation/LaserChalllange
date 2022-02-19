import cv2
import numpy as np
from instrumental.drivers.cameras import uc480

# init camera
instruments = uc480.list_instruments()
cam = uc480.UC480_Camera(instruments[0])

# params
cam.start_live_video(framerate = "10Hz")

while cam.is_open:
     
     frame = cam.grab_image(timeout='100s', copy=True, exposure_time='10ms')
     
     frame1 = np.stack((frame,) * 3,-1) #make frame as 1 channel image
     frame1 = frame1.astype(np.uint8)

     gray = cv2.cvtColor(frame1, cv2.COLOR_BGR2GRAY)
     file1 = open("myfile.txt", "w")
     a=np.sum(frame1)
     file1.writelines(a)
     print(a)


cam.close()    #mozna k nicemu, ale nechci na to sahat
cv2.destroyAllWindows()
