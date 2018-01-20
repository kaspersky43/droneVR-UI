'''
Created on Dec 15, 2016

@author: njand
'''
import socket
import threading
import json
from .Point import Point


class RiftListener:
    def __init__(self, q, ip, port):
        self._ip = ip
        self._port = port
        self._listenUdp = threading.Thread(target=self.recUdp,
                                           args=(q, ))  # need (q, ) need , space otherwise exception. expects a tuple

    '''Starts the background thread for listening for udp messages.'''

    def start(self):
        self._listenUdp.start()

    '''Stops the background thread.'''

    def stop(self):
        self._listenUdp.cancel()

    '''
    METHOD: recUdp
    ARGS: q - the q that can be accessed from the main thread
    DESCRIPTION: Listens for udp messages from the computer running the occulus rift.
    RETURN: nothing.
    '''

    def recUdp(self, q):

        sock = socket.socket(socket.AF_INET,
                             socket.SOCK_DGRAM)
        sock.bind((self._ip, self._port))

        while True:
            # Try and receive data.
            data, addr = sock.recvfrom(1024)

            # If there's any data convert to json
            if data is not None:
                myData = {}
                jsonData = json.loads(data)
                print data + " THIS IS MOVE-TO data"
                for drone in jsonData:
                    points = []
                    waypoints = jsonData[drone]["wp"]
                    for point in waypoints:
                        points.append(Point(point[0], point[1], point[2]))
                    myData[drone] = points
                # Put data onto the queue
                print myData + " THIS IS MOVE-TO myData"
                q.put(myData)
