'''
Created on Feb 1, 2017

@author: njand
'''
import json
from .Point import Point


class MessageBuilder:
    def __init__(self):
        self._takeoff = Point(0, 0, 0)
        self._land = False
        self._end = False
        self._move = Point(0, 0, 0)
        self._stop = False
        self._hasMove = False
        self._hasTakeOff = False
        self._data = {}


    def reset(self):
        self._takeoff.clear()
        self._hasTakeOff = False
        self._land = False
        self._end = False
        self._stop = False
        self._move.clear()
        self._hasMove = False
        self._data.clear()

    def setTakeOff(self, point):
        print 'Setting takeoff: Message Builder'
        self._takeoff.setPoint(point.getX(), point.getY(), point.getZ())
        self._hasTakeOff = True

    def setMove(self, point):
        print 'Setting move: Message Builder'
        self._move.setPoint(point.getX(), point.getY(), point.getZ())
        self._hasMove = True

    def setEnd(self):
        self._end = True

    def setLand(self):
        self._land = True

    def setStop(self):
        self._stop = True

    def build(self):
        if self._hasMove:
            print 'has move'
            self._data['move'] = [self._move.getX(), self._move.getY(),
                                  self._move.getZ()]

        elif self._hasTakeOff:
            print 'has takeoff'
            self._data['takeOff'] = [self._takeoff.getX(), self._takeoff.getY(),
                                     self._takeoff.getZ()]

        elif self._land:
            self._data['land'] = True

        elif self._end:
            self._data['end'] = True

        elif self._stop:
            self._data['stop'] = True

        json_data = None
        if self._hasMove or self._hasTakeOff or self._land or self._end or self._stop:
            json_data = json.dumps(self._data)
        self.reset()
        return json_data
