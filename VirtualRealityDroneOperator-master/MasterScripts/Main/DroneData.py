'''
Created on Dec 15, 2016

@author: njand
'''
'''class - handler for this drones position and attitude'''


class DroneData:
    '''
    METHOD: constructor
    ARGS: droneId - the id of this drone
          point - instance of a Point class - this drones position
          q is quaternion - attitude of this drone
    '''

    def __init__(self, droneId, point, q):
        self._id = droneId
        self._point = point
        self._q = q

    def getPoint(self):
        return self._point

    def getQ(self):
        return self._q

    def getId(self):
        return self._id

    def __str__(self):
        return "id: " + str(self.getId()) + " Location: (" + self.getPoint().__str__() + ") q: " + str(self.getQ())
