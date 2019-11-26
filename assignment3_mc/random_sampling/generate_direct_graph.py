# %%
import matplotlib.pyplot as plt
import numpy
import pandas as pd
import seaborn as sns

# %%
directory = './assignment3_mc/random_sampling/'
# directory = ''
df = pd.read_csv(directory + 'direct_sampling.csv')

# %%
plt.figure(figsize=(20, 20))
sns.lineplot(x=df['particle_number'], y=df['pi'])

plt.savefig(directory + 'direct_sampling_graph.png')

# %%
