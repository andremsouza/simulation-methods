# %%
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import numpy as np

# %%
directory = './assignment3_mc/random_sampling/'
# directory = ''
arr = np.genfromtxt(directory + 'coordinates_good.txt')

# %%
# fig = plt.figure(figsize=(20, 20))
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
# x, y = np.random.rand(2, 100) * 4
x, y = arr[:, 0], arr[:, 1]
hist, xedges, yedges = np.histogram2d(x, y, bins=20, range=[[0, 20], [0, 20]])

# Construct arrays for the anchor positions of the 16 bars.
xpos, ypos = np.meshgrid(xedges[:-1] + 0.25, yedges[:-1] + 0.25, indexing="ij")
xpos = xpos.ravel()
ypos = ypos.ravel()
zpos = 0

# Construct arrays with the dimensions for the 16 bars.
dx = dy = 0.5 * np.ones_like(zpos)
dz = hist.ravel()

ax.bar3d(xpos, ypos, zpos, dx, dy, dz, zsort='average')

# plt.show()
plt.savefig(directory + 'hist3d_good.png')

# %%
# fig = plt.figure(figsize=(20, 20))
fig = plt.figure()
plt.hist2d(x, y, bins=[20, 20], range=[[0, 20], [0, 20]])
plt.savefig(directory + 'hist2d_good.png')

# %%
arr = np.genfromtxt(directory + 'coordinates_bad.txt')

# %%
# fig = plt.figure(figsize=(20, 20))
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
# x, y = np.random.rand(2, 100) * 4
x, y = arr[:, 0], arr[:, 1]
hist, xedges, yedges = np.histogram2d(x, y, bins=20, range=[[0, 20], [0, 20]])

# Construct arrays for the anchor positions of the 16 bars.
xpos, ypos = np.meshgrid(xedges[:-1] + 0.25, yedges[:-1] + 0.25, indexing="ij")
xpos = xpos.ravel()
ypos = ypos.ravel()
zpos = 0

# Construct arrays with the dimensions for the 16 bars.
dx = dy = 0.5 * np.ones_like(zpos)
dz = hist.ravel()

ax.bar3d(xpos, ypos, zpos, dx, dy, dz, zsort='average')

# plt.show()
plt.savefig(directory + 'hist3d_bad.png')

# %%
# fig = plt.figure(figsize=(20, 20))
fig = plt.figure()
plt.hist2d(x, y, bins=[20, 20], range=[[0, 20], [0, 20]])
plt.savefig(directory + 'hist2d_bad.png')

# %%
