'''
Created on Dec 15, 2016

@author: njand
'''
from .RiftListener import RiftListener
from Queue import Queue


class RiftManager:
    def __init__(self, ip, port):
        self._q = Queue()  # Multithreaded queue for background listener to use
        self._riftListener = RiftListener(
            self._q, ip, port)  # background listener thread
        self._riftListener.start()

    '''Stops the thread.'''

    def stop(self):
        self._riftListener.stop()

    '''
    METHOD: getFromQueue
    ARGS: nothing
    DESCRIPTION: checks if the background thread put anything on the queue and
                 returns it back to the Manager class
    RETURN: None - if queue is empty
            moveData - array of moves
    '''

    def getFromQueue(self):
        if self._q.empty():
            return None
        else:
            moveData = []
            while not self._q.empty():
                moveData.append(self._q.get())
            return moveData
