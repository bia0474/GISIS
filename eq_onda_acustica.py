
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

#----------------------------------
# the source
#----------------------------------

# parâmetros
T = 1.0 #tempo total da simulação
dt = 0.0002 #passo temporal

nt = int(T/dt) + 1

# eixo do tempo
t = np.linspace(0, T, nt)

# leitura do binário
fonte = np.fromfile("source.bin", dtype=np.float32)

# plot
plt.figure(figsize=(10,4))

plt.plot(t, fonte)

plt.title("Ricker Wavelet")

plt.xlabel("Tempo (s)")

plt.ylabel("Amplitude")
plt.grid()
plt.show()

#----------------------------------
# plot one snap
#----------------------------------

nx = 2001 #número de pontos espaciais
dx = 0.5 #passo espacial

data = np.fromfile("snapshot_950.bin", dtype=np.float32)

x = np.arange(nx) * dx

plt.plot(x, data)

plt.xlabel("Distance (m)")
plt.ylabel("Amplitude")

plt.title("Wavefield")

plt.grid()
plt.show()

#----------------------------------
# animatiom wave 1D
#----------------------------------

fig, ax = plt.subplots()

line, = ax.plot([], [])

ax.set_xlim(0, nx*dx)
ax.set_ylim(-20, 20)
ax.set_xlabel("Distance (m)")
ax.set_ylabel("Amplitude")

ax.set_title("1D Acoustic Wave")

def update(frame):

    data = np.fromfile(f"snapshot_{frame}.bin", dtype=np.float32)

    x = np.arange(nx) * dx

    line.set_data(x, data)

    return line,

frames = range(50, 5000, 50)

ani = animation.FuncAnimation(fig, update, frames=frames, interval=200, blit=True)

plt.grid()
plt.show()