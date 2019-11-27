# %%
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import seaborn as sns
import math

# %%
directory = './assignment3_mc/random_sampling/'
# directory = ''
pi_arr = np.zeros((1000, 2))
pi_arr[:, 0] = np.linspace(1, 100000000, num=1000)
pi_arr[:, 1] = math.pi

df = pd.read_csv(directory + 'direct_sampling.csv')

pi_const_df = pd.DataFrame(pi_arr, columns=df.columns)
df['type'] = 'sampling'
pi_const_df['type'] = 'PI'
df = df.append(pi_const_df, ignore_index=True)

# %%
# plt.figure(figsize=(20, 20))
sns.lineplot(x=df['particle_number'], y=df['pi'],
             hue=df['type'], dashes=[False, True])

plt.savefig(directory + 'direct_sampling_graph.png')

# %%
