'''
Created on Dec 15, 2016

@author: njand
'''
import socket, json
ip = "127.0.0.1"
port = 6000
message = json.JSONEncoder().encode({"1":{"location":[1,2,3],"Q":[1,2,3,4]}})

sock = socket.socket(socket.AF_INET,
                      socket.SOCK_DGRAM)
sock.sendto(message, (ip, port))
