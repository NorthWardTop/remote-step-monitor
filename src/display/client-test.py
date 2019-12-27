#!/usr/bin/python
# -*- coding: utf-8 -*-

import socket
import time
 
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
addr = ("192.168.1.179", 1234)
 
while True:

    data = "hi server"
    s.sendto(data.encode(), addr)
    time.sleep(1)



s.close()