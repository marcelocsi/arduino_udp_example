# -*- coding: utf-8 -*-
"""
Created on Wed Nov 24 00:05:21 2021

@author: engca
"""
import socket               
import time
 

host = "192.168.100.31" # this is the IP that your ESP32 has gotten from yuour wifi router.
port = 1234             # the port is configured in the arduino code
 

msgFromClient       = "Hello UDP Server - this is Marcelo helping you"
bytesToSend         = str.encode(msgFromClient)
serverAddressPort   = (host, port)
bufferSize          = 1024

# Create a UDP socket at client side
UDPClientSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)

# Send to server using created UDP socket
UDPClientSocket.sendto(bytesToSend, serverAddressPort)

while(True):
    msgFromServer = UDPClientSocket.recvfrom(bufferSize)
    
    msg = "Message from Server {}".format(msgFromServer[0])
    print(msg)

    time.sleep(1)