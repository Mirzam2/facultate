# %%
import numpy as np
import matplotlib.pyplot as plt
import subprocess
start = 0
end = 20
delita = 0.001

process = subprocess.Popen(
    [".\sin", str(start), str(end), str(delita)])
N = int((end-start)//delita)
process.wait()
with open("result.bin") as f:
    data = np.fromfile(f, dtype=np.float32, count=N, offset=0, sep="")
with open("true_result.bin") as f:
    data_true = np.fromfile(f, dtype=np.float32, count=N, offset=0, sep="")
with open("diff_result.bin") as f:
    data_diff = np.fromfile(f, dtype=np.float32, count=N, offset=0, sep="")
with open("break_result.bin") as f:
    data_break = np.fromfile(f, dtype=np.int32, count=N, offset=0, sep="")
x = np.arange(start, end-delita, delita)
# %%

# print(data)
plt.plot(x, data)
#plt.plot(x, data_true)

plt.xlabel(r'x', fontsize=14)
plt.ylabel(r'sin(x)', fontsize=14)
plt.title(r'$График$')
print("HELP")
plt.show()


# %%
plt.plot(x, data_diff)

plt.xlabel(r'x', fontsize=14)
plt.ylabel(r'diff', fontsize=14)
plt.title(r'$График$')
print("HELP")
plt.show()


# %%
plt.plot(x, data_break)

plt.xlabel(r'x', fontsize=14)
plt.ylabel(r'i break', fontsize=14)
plt.title(r'$График$')
print("HELP_break")
plt.show()
# %%
