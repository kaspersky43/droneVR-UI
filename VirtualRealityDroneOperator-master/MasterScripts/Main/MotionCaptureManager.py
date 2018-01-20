'''
Created on Dec 14, 2016

@author: njand
'''
from .MotionCaptureListener import MotionCaptureListener


class MotionCaptureManager:
    '''
    METHOD: constructor
    ARGS: managerMocapCallback - function to get access back to Manager
    '''

    def __init__(self, ip, port, managerMocapCallback):
        self._managerMocapCallback = managerMocapCallback
        self._polling = MotionCaptureListener(
            ip, port, self.motionCaptureDataCallback)
        self._polling.start()

    '''Calls the cancel thread on the listener class.'''

    def cancel(self):
        self._polling.cancel()

    '''
    METHOD: motionCaptureDataCallback
    ARGS: data - droneData class instance with drone data in it (position, attitude)
    DESCRIPTION: - continues passing data back to the main manager class
    RETURN: nothing
    '''

    def motionCaptureDataCallback(self, data):
        self._managerMocapCallback(data)
