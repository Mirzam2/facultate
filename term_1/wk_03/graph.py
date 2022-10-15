#%%
import numpy as np
import json
import matplotlib.pyplot as plt
import subprocess
w = 1
x_0 = 1
v_0 = 0
N = 10000000
dt = 10**-3
process = subprocess.Popen([".\eiler", str(w), str(x_0), str(v_0),str(N),str(dt)])
process.wait()
with open("results_x.bin") as f:
    data_x = np.fromfile(f, dtype=np.float32, count=N, offset=0, sep="")
with open("results_v.bin") as f:
    data_v = np.fromfile(f, dtype=np.float32, count=N, offset=0, sep="")
with open("results_x_abs.bin") as f:
    data_x_abs = np.fromfile(f, dtype=np.float32, count=N, offset=0, sep="")
with open("results_E.bin") as f:
    data_E = np.fromfile(f, dtype=np.float32, count=N, offset=0, sep="")
#%%
x = np.arange(0, N)
plt.plot(x, data_x)
plt.plot(x, data_x_abs)
plt.xlabel(r't', fontsize=14)
plt.ylabel(r'X', fontsize=14)
plt.title(r'$График$')
print("HELP")
plt.show()

# %%
plt.plot(x, data_E)
plt.xlabel(r't', fontsize=14)
plt.ylabel(r'E', fontsize=14)
plt.title(r'$График \ E$')
plt.show()

# %%
plt.plot(data_x, data_v)
plt.xlabel(r'x', fontsize=14)
plt.ylabel(r'v', fontsize=14)
plt.title(r'$Фазовая \ диаграмма$')
plt.show()
# %%
Analis_E=np.arange(5)
for j in range(5):
    process = subprocess.Popen([".\eiler", str(w), str(x_0), str(v_0),str(N),str(dt)])
    process.wait()
    with open("results_E.bin") as f:
        data_E = np.fromfile(f, dtype=np.float32, count=N, offset=0, sep="")
    Analis_E[j] = data_E[N-1]
    dt/=10
    N*=10
    
plt.plot(np.arange(5), Analis_E)
plt.xlabel(r'j', fontsize=14)
plt.ylabel(r'E', fontsize=14)
plt.title(r'$Ошибка \ энергии \ от \ dt$')
plt.show()
# %%
