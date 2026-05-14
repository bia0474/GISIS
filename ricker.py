import numpy as np
import matplotlib.pyplot as plt

nt = 101

array = np.fromfile("fonte_sismica.bin", dtype = np.float32, count = nt)


plt.xlabel("Distance (m)")
plt.ylabel("Amplitude")

plt.title("Ricker")
plt.plot(array)
plt.show()