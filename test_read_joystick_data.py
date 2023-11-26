import serial
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib import cm
from matplotlib.ticker import LinearLocator, FixedLocator, FormatStrFormatter
import matplotlib

class plot2dClass( object ):

    def __init__( self, systemSideLength, lowerCutoffLength):
        self.systemSideLength = systemSideLength
        self.lowerCutoffLength = lowerCutoffLength
        self.fig = plt.figure()
        self.ax = self.fig.add_subplot( 111 )
        self.ax.set_xlim(-1, 1)
        self.ax.set_ylim(-1, 1)
        self.vect = self.ax.plot([0.5],[0.5])
        

    def drawNow( self, vect , color = True):
        self.ax.cla()
        self.ax.set_xlim(-1, 1)
        self.ax.set_ylim(-1, 1)
        self.ax.invert_yaxis()
        if color:
            self.vect = self.ax.plot(vect[0],vect[1], 'bo')
        else :
            self.vect = self.ax.plot(vect[0],vect[1], 'ro')
        plt.draw()                      # redraw the canvas
        self.fig.canvas.flush_events()

    
def plot_live_mouse():
    matplotlib.interactive(True)
    arduino = serial.Serial(port='COM16', baudrate=9600, timeout=.1)
    p2 = plot2dClass(5,1)
    while True:
        val = arduino.readline()
        
        if val == bytes(0):
            1+1
        else :
            rawdata = val.decode("utf-8").rstrip().split(',')
            # print(rawdata)
            if len(rawdata) == 3 :
                try:
                    pos = [float(rawdata[i]) for i in range(2)]
                    state = float(rawdata[2])
                    print(state)
                    p2.drawNow(pos)
                except:
                    continue

plot_live_mouse()

