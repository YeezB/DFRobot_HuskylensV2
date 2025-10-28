'''!
  @file ObjectRecognitionNo_X.py
  @brief Sample code for obtaining information about objects ID.X(ID.0)
  @If multiple targets are detected simultaneously, 
  @you can modify the parameters of getCachedResultByID() to adjust which target is printed.
  
  @copyright  Copyright (c) 2025 DFRobot Co.Ltd (http://www.dfrobot.com)
  @license    The MIT License (MIT)
  @author     [YeezB](zibin.ye@dfrobot.com)
  @version    V1.0
  @date       2025-10-28
  @url https://github.com/DFRobot/DFRobot_HuskylensV2
'''

from pinpong.board import Board
import sys
import os
sys.path.append("../")
from dfrobot_huskylensv2 import *

Board("rpi").begin()
Board().begin()
huskylens = HuskylensV2_I2C()
huskylens.knock()
huskylens.switchAlgorithm(ALGORITHM_OBJECT_RECOGNITION)

while True:
    huskylens.getResult(ALGORITHM_OBJECT_RECOGNITION)
    if  ((huskylens.getCachedResultByID(ALGORITHM_OBJECT_RECOGNITION, 1) is not None)):
        print(str("Name: ") + str(huskylens.getCachedResultByID(ALGORITHM_OBJECT_RECOGNITION,1).name))
        print(str("xCenter: ") + str(huskylens.getCachedResultByID(ALGORITHM_OBJECT_RECOGNITION,1).xCenter))
        print(str("yCenter: ") + str(huskylens.getCachedResultByID(ALGORITHM_OBJECT_RECOGNITION,1).yCenter))
        print(str("Width: ") + str(huskylens.getCachedResultByID(ALGORITHM_OBJECT_RECOGNITION,1).width))
        print(str("Height: ") + str(huskylens.getCachedResultByID(ALGORITHM_OBJECT_RECOGNITION,1).height))
    time.sleep(0.1)