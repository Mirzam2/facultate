from cmath import pi
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
A = 1
B = 1
a = pi
b = pi / 2
d = pi / 4
d = np.linspace(0, 2*np.pi, 100)
N_row = 2
N_cols = 2
def one_graph(t,i,j,d):
    x = np.cos(a * t + d) * A
    y = np.sin(b * t) * B
    axes[i][j].plot(x,y,color='g')
def anime(d):
    t = np.linspace(0, 2*np.pi, 100)
    for i in range(N_row):
        for j in range(N_cols):
            one_graph(t,i,j,d)
    return fig
    plt.show()



def init():
    plt.plot([-A,A],[B,B], color = "w")
    plt.xlabel("x")
    plt.ylabel("y")


fig, axes = plt.subplots(nrows = N_row, ncols =2)
anim = FuncAnimation(fig, anime, frames=d, #init_func=init,
                     interval=20, blit=True)
plt.show()
