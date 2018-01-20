'''
Created on Dec 14, 2016

@author: njand
'''

from .DroneData import DroneData
from .Point import Point
from TestMotionCaptureData.TestMoCapData import TestMoCapData
import threading
import json
import socket

'''Class to listen for data from motion capture system.'''


class MotionCaptureListener:

    def __init__(self, ip, port, motionCaptureDataCallback):
        self._ip = ip
        self._port = port
        self._motionCapCallback = motionCaptureDataCallback
        self._thread = threading.Thread(target=self.run, args=())
    '''
    METHOD: run
    ARGS: nothing
    DESCRIPTION: - sets up a udp listener for messages from the motion capture system.
    RETURN: nothing
    '''

    def run(self):
        self._socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self._socket.bind((self._ip, self._port))

        # Poll for data
        while True:
            data, addr = self._socket.recvfrom(4196) # 4196

            self.handleDataPacket(data)

        self._socket.close()

    '''Starts the thread.'''

    def start(self):
        self._thread.start()

    '''Cancels the thread.'''

    def cancel(self):
        self._thread.cancel()

    '''
    METHOD: handleDataPacket
    ARGS: tempData - udp packet
    DESCRIPTION: takes udp packet converts it and the passes it back to the motion capture manager class
    RETURN: nothing
    '''

    def handleDataPacket(self, tempData):

        # Test data
        # tempData = self.getTestData()

        # parseData
        droneData = self.parseData(tempData)

        # pass data back to motion capture manager.
        self._motionCapCallback(droneData)

    '''
    METHOD: parseData
    ARGS: data - udp packet
    DESCRIPTION: converts udp packet to json data and fills droneData class for each drone.
    RETURN: returnData - array of DroneData classes
    '''

    def parseData(self, data):
        returnData = []
        messageData = json.loads(data)

        for drone in messageData:
            location = messageData[drone]["location"]
            q = messageData[drone]["Q"]

            ''' y and z are flipped'''
            point = Point(location[0], location[2], location[1])
            droneData = DroneData(drone, point, q)
            returnData.append(droneData)
            print returnData + " THIS IS DRONE RETURN DATA FROM MOCAPLISTENER"
        return returnData

    '''Just for testing'''

    def getTestData(self):
        testData = TestMoCapData()
        return testData.getData()
