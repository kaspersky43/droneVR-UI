'''
Created on Dec 14, 2016

@author: njand
'''

from .Point import Point
from Queue import Queue
from math import sqrt, pow
from .MessageBuilder import MessageBuilder
import socket


class Drone:
    def __init__(self, droneId, ip, port):
        # holds current location of the drone
        self._currentLocation = Point(0, 0, 0)
        self._previousLocation = Point(0, 0, 0)
        # holds the current target of the drone
        self._destination = Point(0, 0, 0)
        self._id = droneId  # this drones id
        self._ip = ip  # this drones ip address
        self._port = port  # the port to broadcast to
        self._state = self.State()  # the current state of the drone.
        self._waitToShutDown = False  # are we cleaning up the drone to shutdown?
        self._queuedMoves = Queue()  # any moves currently in the queue
        # How close to the destination should we be, TODO: what should this be?
        self._targetDegreeOfOffset = .1
        # Message builder class for the messages being sent to the drone.
        self._messageBuilder = MessageBuilder()
        self._landedCounter = 0  # counter to handle landing.
        self._debug = True  # Are we debuging.
        self._notSafe = False

        # Set up udp connection with drone.
        self._s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    '''
    METHOD: update
    ARGS: droneData this drones current position and attitude
    DESCRIPTION: update drones state and send off any messages as needed.
    RETURN: nothing
    '''

    def update(self):
        if(self._notSafe):
            self._notSafe = False

        '''if self.checkHasLanded(self._previousLocation):
            self._state.setToGround()
            if self._waitToShutDown:
                self.handleShutDown()'''

        # check if we're close enough to destination to go onto the next move
        if not self._queuedMoves.empty():
            if self.checkIfWeCanGoToNextMove(self._currentLocation) or self._state.getCurrentState() == self.State.GROUND:
                self.move()

        # Build the message
        message = self._messageBuilder.build()
        if message is not None:
            print "SENT MESSAGE TO DRONE"
            self._s.sendto(message, (self._ip, self._port))

    def setNotSafe(self, point):
        self._notSafe = True  # set to not safe
        self.newMove(point)  # queue the moves#
        self.move()  # call move so it's added to the message

    '''
    METHOD: move
    ARGS: point - destination of the move
    DESCRIPTION: Based on the drones state create the move.
    RETURN: nothing.
    '''

    def move(self):
        point = self._queuedMoves.get()
        # Hasn't taken off.
        if self._state.getCurrentState() == self.State.GROUND:
            print 'On ground adding takeoff'
            print point
            self.updateDestination(point)

            # Set takeoff message
            self._messageBuilder.setTakeOff(point)

            # update state
            self._state.setToTakeOff()

        elif self._state.getCurrentState() == self.State.FLYING or self._state.getCurrentState() == self.State.TAKINGOFF:

            if self._state.getCurrentState() == self.State.TAKINGOFF:
                self._state.setToFlying()

            self.updateDestination(point)
            # If Z is set to 0 set up a landing move.
            if point.getZ() == 0:
                self._messageBuilder.setLand()
                self._state.setToLand()
            else:
                print point
                self._messageBuilder.setMove(point)

    '''
    METHOD: newMove
    ARGS: point - destination of new move
    DESCRIPTION: - Overrides any queued moves and sets this new move.
    RETURN: nothing
    '''

    def newMove(self, points):
        print 'new Move'
        if not self._notSafe:
            if not self._queuedMoves.empty():
                self._queuedMoves.queue.clear()

            for point in points:
                self._queuedMoves.put(point)
        else:
            if not self._queuedMoves.empty():
                self._queuedMoves.queue.clear()
            self._queuedMoves.put(points)

    '''
    METHOD: checkIfWeCanGoToNextMove
    ARGS: location - Point of currentLocation
    DESCRIPTION: checks if we're close enough to destination to move on to next move.
    RETURN: true - we can or false - we can't
    '''

    def checkIfWeCanGoToNextMove(self, location):
        distanceToTarget = sqrt(pow(location.getX() - self._destination.getX(), 2) +
                                pow(location.getY() - self._destination.getY(), 2) +
                                pow(location.getZ() - self._destination.getZ(), 2))
        print 'Distance to target ' + str(distanceToTarget)
        if distanceToTarget <= self._targetDegreeOfOffset:
            return True
        return False
    '''
    METHOD: checkHasLanded
    ARGS: point - this updates current location before self._currentLocation is updated
    DESCRIPTION: check if this updates location and last update is the same (if yes update landed counter)
                 if landed counter = 10 we have landed - last 10 updates are the same
    RETURN: True - we've landed
            False - we haven't
    '''

    def checkHasLanded(self, point):
        if (self._currentLocation.getX() == point.getX() and
            self._currentLocation.getY() == point.getY() and
                self._currentLocation.getZ() == point.getZ()):
            self._landedCounter += 1
            if self._landedCounter == 10:
                self._landedCounter = 0
                return True
        else:
            self._landedCounter = 0
        return False

    '''update the current destination we're heading to.'''

    def updateDestination(self, point):
        self._destination.setPoint(point.getX(),
                                   point.getY(),
                                   point.getZ())

    '''update our currentLocation.'''

    def updateCurrentLocation(self, point):
        self._previousLocation.setPoint(self._currentLocation.getX(
        ), self._currentLocation.getY(), self._currentLocation.getZ())
        self._currentLocation.setPoint(point.getX(),
                                       point.getY(),
                                       point.getZ())

    '''Internal State class - LANDING, FLYING, on the GROUND. '''
    class State:
        LANDING = "LANDING"
        FLYING = "FLYING"
        GROUND = "GROUND"
        TAKINGOFF = "TAKINGOFF"

        def __init__(self):
            self._currentState = self.GROUND

        def getCurrentState(self):
            return self._currentState

        def setToLand(self):
            print 'Set to landing'
            self._currentState = self.LANDING

        def setToGround(self):
            print 'Set to ground'
            self._currentState = self.GROUND

        def setToTakeOff(self):
            print 'Set to takingoff'
            self._currentState = self.TAKINGOFF

        def setToFlying(self):
            print 'Set to flying'
            self._currentState = self.FLYING
