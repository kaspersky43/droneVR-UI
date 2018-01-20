'''
Created on Dec 14, 2016

@author: Nick
'''
from .DroneController import DroneController
from .DroneController import MessageToDroneController
from .MotionCaptureManager import MotionCaptureManager
from .RiftManager import RiftManager
from .Point import Point
from .FindIP import get_ip_address


class Manager:
    #RIFTPCIP = "169.254.133.48"
    RIFTPCIP = "0.0.0.0"
    RIFTPORT = 63819
    MOTIONCAPTUREIP = "0.0.0.0"
    MOTIONCAPTUREPORT = 6000
    # (id, ip) Array of drones that will be in the system.
    DRONES = [('1', '192.168.1.111')]
    DRONEPORT = 5068
    MIN_BOUNDARY = Point(-2.6, -2.1, 0.08)  # Min x, Min y, Min z (meters)
    MAX_BOUNDARY = Point(2.7, 1.4, 2.35)  # Max x, Max y, Max z (meters)
    ZONE_OF_SAFETY_RADIUS = .75  # .1 for now.

    def __init__(self):
        # Handles messages from the Oculus rift (move, takeoff, land, end)
        self._riftManager = RiftManager(self.RIFTPCIP, self.RIFTPORT)

        # initialize drone controller first and wait to connect to all drones before starting polling
        # Handles all connections to the different drones and sends out messages to drones
        self._droneController = DroneController(self.DRONES, self.MIN_BOUNDARY,
                                                self.MAX_BOUNDARY, self.ZONE_OF_SAFETY_RADIUS, self.DRONEPORT)

        # Handles messages from the motion capture system for drone position and attitude
        self._motionCaptureManager = MotionCaptureManager(
            self.MOTIONCAPTUREIP, self.MOTIONCAPTUREPORT, self.managerMocapCallback)

    def cancel(self):
        self._motionCaptureManager.cancel()

    '''
    METHOD: managerMocapCallback
    ARGS: data - dronedata class that holds drone attitude and position
    DESCRIPTION: - gives the motion controller a way to pass data back to the Manager class
    RETURN: nothing
    '''

    def managerMocapCallback(self, data):
        messageToDroneController = MessageToDroneController()
        # Add drone data
        messageToDroneController.addToDroneData(data)

        # Check if there's any drone move commands from rift.
        moveData = self._riftManager.getFromQueue()

        if moveData is not None:
            print moveData + " THIS IS moveData FROM managerMocapCallback"
            messageToDroneController.addToMoveData(moveData)

        self._droneController.update(messageToDroneController)
