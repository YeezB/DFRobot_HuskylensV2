'''!
  @file CenterObjectRecognition.py
  @brief Sample code for obtaining information about objects near the center
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


Board("rpi").begin()#Comment this line when using UNIHIKER M10
Board().begin()

huskylens = HuskylensV2_I2C()
huskylens.knock()
huskylens.switchAlgorithm(ALGORITHM_OBJECT_RECOGNITION)

while True:
    huskylens.getResult(ALGORITHM_OBJECT_RECOGNITION)
    if  (huskylens.available(ALGORITHM_OBJECT_RECOGNITION)):
        print(str("ID: ") + str(huskylens.getCachedCenterResult(ALGORITHM_OBJECT_RECOGNITION).ID))
        print(str("Name: ") + str(huskylens.getCachedCenterResult(ALGORITHM_OBJECT_RECOGNITION).name))
        print(str("xCenter: ") + str(huskylens.getCachedCenterResult(ALGORITHM_OBJECT_RECOGNITION).xCenter))
        print(str("yCenter: ") + str(huskylens.getCachedCenterResult(ALGORITHM_OBJECT_RECOGNITION).yCenter))
        print(str("Width: ") + str(huskylens.getCachedCenterResult(ALGORITHM_OBJECT_RECOGNITION).width))
        print(str("Height: ") + str(huskylens.getCachedCenterResult(ALGORITHM_OBJECT_RECOGNITION).height))
    time.sleep(0.1)