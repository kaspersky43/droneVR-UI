'''
Created on Dec 15, 2016

@author: njand
'''
import socket, json
#ip = "169.254.26.174"
ip = "127.0.0.1"
port = 63819
message = json.JSONEncoder().encode({"1":{"wp":[[0, 0, 1],[0,1,1]]}})

sock = socket.socket(socket.AF_INET,
                      socket.SOCK_DGRAM)
sock.sendto(message, (ip, port))
