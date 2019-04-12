import matplotlib
matplotlib.use("TkAgg")
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg, NavigationToolbar2Tk
from matplotlib.figure import Figure

import matplotlib.animation as animation
from matplotlib import  style

import datetime
import matplotlib.pyplot as plt
import numpy as np

import os


import tkinter as tk
from tkinter import *

style.use("classic")

counter = 0
f = plt.figure(figsize=(15,5),dpi=100)
a = f.add_subplot(111)
extra = []
zList = []
plt.rc('xtick', labelsize=7)
plt.rc('ytick', labelsize=7)
plt.margins(0.2)
plt.subplots_adjust(left=0.04, bottom=0.11, right=.99, top=0.96)





def animate(i):
    dataTime = datetime.datetime.now()
    xList = []
    yList = []
    global zList
    global counter
    global entry_1
    counter = counter + 1
    extra.append(dataTime.strftime("%H:%M"))

    with open("putty.txt", "rb") as f:
        f.seek(-2, os.SEEK_END)     # Jump to the second last byte.
        while f.read(1) != b"\n":   # Until EOL is found...
            f.seek(-2, os.SEEK_CUR) # ...jump back the read byte plus one more.
        last = f.readline().decode()         # Read last line and decode into string

    f.close();
    x, y, z, clearness, cloudyness = last.split(',') #split line commas
    xList.append(float(x))
    yList.append(float(y))
    zList.append(float(z)) #This is the difference value
    clear_line=float(clearness)
    cloudy_line=float(cloudyness)
    
            
    if (counter < 144): #if counter has not reached the value then keep plotting the lists
        a.clear()
        plt.xlabel('Time')
        plt.xticks(rotation='vertical')
        plt.ylabel('Difference Temp (C)')
        plt.hlines(clear_line,0,1+counter,colors='green',linestyles='dashed')
        plt.hlines(cloudy_line,0,1+counter,colors='red',linestyles='dashed')
        a.plot(extra, zList)
        
    else: #clear lists once finished counter 
        a.clear()
        plt.xticks(rotation='vertical')
        plt.xlabel('Time')
        plt.ylabel('Difference Temp (C)')
        plt.hlines(clear_line,0,1+counter,colors='green',linestyles='dashed')
        plt.hlines(cloudy_line,0,1+counter,colors='red',linestyles='dashed')
        a.plot(extra,zList)
        xList.clear()
        yList.clear()
        zList.clear()
        extra.clear()
        counter = 0
    
            
            


root = Tk()




canvas = FigureCanvasTkAgg(f, root)
canvas.draw()
toolbar = NavigationToolbar2Tk(canvas, root)
toolbar.update()
canvas.get_tk_widget().pack(side=tk.TOP, fill=tk.BOTH, expand=True)

ani = animation.FuncAnimation(f, animate, interval=600000) #update graph every 10 minutes
#ani = animation.FuncAnimation(f, animate, interval=1000)


root.mainloop()


