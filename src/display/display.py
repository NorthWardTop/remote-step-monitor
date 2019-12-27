#!/usr/bin/python
# -*- coding: utf-8 -*-

# import socket
# import struct

# import numpy as np

# from matplotlib import pyplot as plt
# from matplotlib import animation as antt
# from mpl_toolkits.mplot3d import Axes3D

# s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
# s.bind(("192.168.1.104", 1234))
# print("UDP bound on port 1234...")


# while True:
#     raw_data, addr = s.recvfrom(14)
#     # print("Receive from %s:%s" % addr)
#     data = struct.unpack("hhhhhhh", raw_data)
#     print(data)
#     print(data[0], data[1])
#     plt.show()


# s.close()





import socket
import struct
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation



s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.bind(("192.168.1.104", 1234))
print("UDP bound on port 1234...")

fig, ax = plt.subplots()
# x = np.arange(-17000, 17000, 1)
x = np.arange(-1, 1, 0.001)
line, = ax.plot(x, 'r')

AccelScaleFactor = 16384
GyroScaleFactor = 131


def init():  # only required for blitting to give a clean slate.
    line.set_ydata([np.nan] * len(x))
    return line,
 

def animate(i):
    raw_data, addr = s.recvfrom(14)
    # print("Receive from %s:%s" % addr)
    data = struct.unpack("hhhhhhh", raw_data)
    print(data)
    line.set_ydata(data[0]/AccelScaleFactor)  # update the data.
    return line,


ani = animation.FuncAnimation(
    fig, animate, init_func=init, interval=2, blit=True, save_count=50)
#    fig, animate, interval=2, blit=True)



# To save the animation, use e.g.
#
# ani.save("movie.mp4")
#
# or
#
# from matplotlib.animation import FFMpegWriter
# writer = FFMpegWriter(fps=15, metadata=dict(artist='Me'), bitrate=1800)
# ani.save("movie.mp4", writer=writer)

plt.show()

