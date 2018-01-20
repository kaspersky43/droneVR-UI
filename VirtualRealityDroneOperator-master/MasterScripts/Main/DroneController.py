'''
Created on Dec 14, 2016

@author: njand
'''

from .Drone import Drone
from .Point import Point
from math import sqrt


class DroneController:
    '''
    METHOD: constructor
    ARGS: drones - list of drones with there id and and ip address
          minBoundary - minimum boundary of the room
          maxBoundary - maximum --------------------
          radiusOfSafety - the zone around a drone that other objects can't be in.
    '''

    def __init__(self, drones, minBoundary, maxBoundary, radiusOfSafety, port):
        # Create a dictionary of Drone instances (key - id of drone)
        self._drones = {}
        for droneId, ip in drones:
            self._drones[droneId] = Drone(droneId, ip, port)

        self._minBound = minBoundary
        self._maxBound = maxBoundary
        self._radiusOfSafety = radiusOfSafety

    '''
    METHOD: update
    ARGS: data - instance of MessageToDroneController class holds all drone positions and attitudes plus any move commands
    DESCRIPTION: - called each time a new motion capture message is received.
                  checks safety of each drone position and the safety of any move commands
    RETURN: nothing
    TODO: update for multiple drones - kind of penciled out at the moment.
    '''

    def update(self, data):
        droneData = data.getDroneData()
        moveData = data.getMoveData()
        self.distributeCurrentLocation(droneData)
        self.checkAgainstEachOther(droneData)
        self.checkAgainstBoundaries(droneData)

        if moveData is not None:
            self.handleMoveData(moveData)

        for key in self._drones.keys():
            self._drones[key].update()

    '''
    METHOD: distributeCurrentLocation
    ARGS: droneData - array of DroneData instances
    DESCRIPTION: Set each drones current position.
    RETURN: nothing
    '''

    def distributeCurrentLocation(self, droneData):
        for drone in droneData:
            self._drones[drone.getId()].updateCurrentLocation(drone.getPoint())

    '''
    METHOD: checkAgainstEachOther
    ARGS: droneData - array of DroneData instances
    DESCRIPTION: checks drones against drones
    RETURN: nothing
    '''

    def checkAgainstEachOther(self, droneData):
        for i in range(0, len(droneData)):
            for j in range(i + 1, len(droneData)):
                if not self.checkDistance(droneData[i].getPoint(), droneData[j].getPoint()):
                    self._drones[droneData[i].getId()].setNotSafe(
                        droneData[i].getPoint())
                    self._drones[droneData[j].getId()].setNotSafe(
                        droneData[j].getPoint())

    '''
    METHOD: checkDistance
    ARGS: drone, otherDrone - droneData instances
    DESCRIPTION: check distance between 2 points.
    RETURN: true - safe
            false - not safe
    '''

    def checkDistance(self, drone, otherDrone):
        dist = sqrt((drone.getX() - otherDrone.getX())**2 + (drone.getY() - otherDrone.getY())**2 +
                    (drone.getZ() - otherDrone.getZ())**2)

        if dist < self._radiusOfSafety:
            return False
        return True

    '''
    METHOD: checkAgainstBoundaries
    ARGS: droneData
    DESCRIPTION: checks against the boundaries of the room.
    RETURN: nothing
    '''

    def checkAgainstBoundaries(self, droneData):
        for drone in droneData:
            safe2 = False
            safe = False
            safe, point = self.testAgainstWallsAndCeiling(drone.getPoint())

            if self._drones[drone.getId()]._state.getCurrentState() == Drone.State.FLYING:
                safe2, point = self.testAgainstFloor(point)
            if safe or safe2:
                self._drones[drone.getId()].setNotSafe(point)
                print 'Drone not safe boundaries'

    '''
    METHOD: testAgainstFloor
    ARGS: droneData
    DESCRIPTION: checks against the floor of the room.
    RETURN: nothing
    '''

    def testAgainstFloor(self, point):
        distToFloor = point.getZ() - self._minBound.getZ() + .25
        if distToFloor <= self._radiusOfSafety:
            print "Original point " + str(point)
            point.setPoint(point.getX(), point.getY(),
                           point.getZ() + self._radiusOfSafety)
            print "Test against the floor " + str(point)
            return True, point
        return False, point

    def testAgainstWallsAndCeiling(self, locationData):
        safe = False
        x = locationData.getX()
        y = locationData.getY()
        z = locationData.getZ()

        # check against ceiling = max bound z
        distToCeiling = self._maxBound.getZ() - z + .25
        if distToCeiling <= self._radiusOfSafety:
            safe = True
            z = z - self._radiusOfSafety

        # check against left wall = min x
        distToLeftWall = x - self._minBound.getX() + .25
        if distToLeftWall <= self._radiusOfSafety:
            safe = True
            x = x + self._radiusOfSafety

        # check against right wall = max x
        distToRightWall = self._maxBound.getX() - x + .25
        if distToRightWall <= self._radiusOfSafety:
            safe = True
            x = x - self._radiusOfSafety

        # check against front wall = max y
        distToFrontWall = self._maxBound.getY() - y + .25
        if distToFrontWall <= self._radiusOfSafety:
            safe = True
            y = y - self._radiusOfSafety

        # check against back wall = min y
        distToBackWall = y - self._minBound.getY() + .25
        if distToBackWall <= self._radiusOfSafety:
            safe = True
            y = y + self._radiusOfSafety
        # Split this up if we want to decide what wall we're closest to.
        if safe:
            point = Point(x, y, z)
            print "Original point " + str(locationData)
            print "New point " + str(point)
            return safe, point
        return safe, locationData

    def handleMoveData(self, moveData):
        for data in moveData:
            for key in data.keys():
                self._drones[key].newMove(data[key])


'''Container class for move data and position data data from Manager to DroneController.
'''


class MessageToDroneController:
    def __init__(self):
        self._droneData = None
        self._moveData = None

    def addToDroneData(self, data):
        self._droneData = data

    def addToMoveData(self, data):
        self._moveData = data

    def getDroneData(self):
        return self._droneData

    def getMoveData(self):
        return self._moveData
