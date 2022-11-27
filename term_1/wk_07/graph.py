# %%
import numpy as np
import matplotlib.pyplot as plt
import subprocess
N = 100000
delita = 0.001
x0 = 1
v0 = 0
process = subprocess.Popen(
    [".\main", str(N), str(delita), str(x0), str(v0)])
process.wait()
with open("data.txt") as f:
    data = np.loadtxt(f)
data_trans = data.transpose()
t = np.arange(0, N*delita, delita)
# %%
print(data[0])
#%%
# print(data)
plt.plot(t, data_trans[0])
#plt.plot(x, data_true)

plt.xlabel(r't', fontsize=14)
plt.ylabel(r'sin(x)', fontsize=14)
plt.title(r'$График$')
print("HELP")
plt.show()


# %%

energy = data_trans[0]**2/2 + data_trans[1] ** 2 / 2
plt.plot (t,energy)
plt.xlabel(r't', fontsize=14)
plt.ylabel(r'E', fontsize=14)
plt.title(r'$Энергия$')
print("HELP")
plt.show()
# %%
