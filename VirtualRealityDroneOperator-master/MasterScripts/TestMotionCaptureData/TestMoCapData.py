'''
Created on Dec 15, 2016

@author: njand
'''
import json
class TestMoCapData:
    def __init__(self):
        '''self._data = json.JSONEncoder().encode([{"id": 1, "location": [1, 2, 3], "q": [1, 0, 0, 0]},
                                                         {"id": 2, "location": [0, 2, 0], "q": [1, 0, 0, 0]}])
        '''
        self._data = json.JSONEncoder().encode({"1":{"Location":[0,0,0.7],"Q":[1,0,0,0]}})
    def getData(self):
        return self._data