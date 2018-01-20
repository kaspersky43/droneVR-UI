'''
Created on Dec 14, 2016

@author: njand
'''
'''class that handles xyz points.'''


class Point:
    def __init__(self, x, y, z):
        self._x = x
        self._y = y
        self._z = z

    def setPoint(self, x, y, z):
        self._x = x
        self._y = y
        self._z = z

    def getX(self):
        return self._x

    def getY(self):
        return self._y

    def getZ(self):
        return self._z

    def clear(self):
        self._x = 0
        self._y = 0
        self._z = 0

    def __str__(self):

        return "x: " + str(self.getX()) + " y: " + str(self.getY()) + " z: " + str(self.getZ())
