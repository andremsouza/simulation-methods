# %%
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns

# %%
print("Loading file...")
directory = "./assignment4_ca/"
df = pd.read_csv(directory + "fractal_output_1.csv")
print("DataFrame loaded...")

# %%
print("Plotting...")
sns.set()
sns.lineplot(data=df, x="t", y="r_gyration", hue="p", legend="full")
plt.savefig(directory + "fractal_graphs_1.png")
plt.show()
print("Done")

# %%
