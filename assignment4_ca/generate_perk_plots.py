# %%
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns

# %%
directory = "./assignment4_ca/"
df = pd.read_csv(directory + "perk_output.csv")

# %%
sns.set()
# call regplot on each axes
fig, (ax1, ax2) = plt.subplots(ncols=2, sharey=False, sharex=True, figsize=(10, 10))
sns.lineplot(data=df, x="p", y="avg_max_cluster", hue="n_grid", legend="full", ax=ax1)
sns.lineplot(
    data=df,
    x="p",
    y="probability_spanning_cluster",
    hue="n_grid",
    legend="full",
    ax=ax2,
)
plt.savefig(directory + "perk_graphs.png")
plt.show()

# %%


# %%
