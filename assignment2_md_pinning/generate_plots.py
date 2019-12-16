# %%
import matplotlib.pyplot as plt
import seaborn as sns
import numpy as np

# %%
sizes = [32, 64, 128, 256]
forces = [1.0, 1.5, 2.0, 2.5, 3.0]
directory = "./assignment2_md_pinning/"

# %%
files = {
    size: {
        int(force * 10): directory
        + "statistics_"
        + str(size)
        + "_"
        + str(int(force * 10))
        + ".txt"
        for force in forces
    }
    for size in sizes
}
files[0] = {0: directory + "statistics_0.txt"}

# %%
statistics = {
    size: {force: np.genfromtxt(files[size][force]) for force in files[size]}
    for size in files
}

# %%
plt_idx = 1
sns.set()
fig, ax = plt.subplots(figsize=(50, 50))
fig.suptitle("Average force in each simulation", fontsize=16)

for idx, force in enumerate(forces):
    ax = plt.subplot(len(sizes) + 1, len(forces), plt_idx)
    ax.set_title("statistics_0.txt")
    sns.lineplot(x=statistics[0][0][:, 0], y=statistics[0][0][:, 1])
    plt.xlim([0, 2.0])
    plt_idx += 1

for size in sorted(list(statistics.keys())[:-1]):
    for force in sorted(statistics[size].keys()):
        ax = plt.subplot(len(sizes) + 1, len(forces), plt_idx)
        ax.set_title("statistics_" + str(size) + "_" + str(int(force)) + ".txt")
        sns.lineplot(x=statistics[size][force][:, 0], y=statistics[size][force][:, 1])
        plt.ylim([0, 2.0])
        plt_idx += 1
plt.savefig(directory + "output_graphs.png")
plt.show()

# %%
