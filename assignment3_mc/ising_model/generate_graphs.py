# %%
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import seaborn as sns
import math

# %%
directory = './assignment3_mc/ising_model/'
# directory = ''
# pi_arr = np.zeros((1000, 2))
# pi_arr[:, 0] = np.linspace(1, 100000000, num=1000)
# pi_arr[:, 1] = math.pi

df = pd.read_csv(directory + 'output.csv')

# pi_const_df = pd.DataFrame(pi_arr, columns=df.columns)
# df['type'] = 'sampling'
# pi_const_df['type'] = 'PI'
# df = df.append(pi_const_df, ignore_index=True)

# %%
# plt.figure(figsize=(20, 20))
sns.lineplot(x=df['T'], y=df['|M|'])

plt.savefig(directory + 'ising_model_m.png')

# %%
# plt.figure(figsize=(20, 20))
sns.lineplot(x=df['T'], y=df['|E|'])

plt.savefig(directory + 'ising_model_e.png')

# %%
# plt.figure(figsize=(20, 20))
sns.lineplot(x=df['T'], y=df['chi'])

plt.savefig(directory + 'ising_model_chi.png')

# %%
# plt.figure(figsize=(20, 20))
sns.lineplot(x=df['T'], y=df['cv'])

plt.savefig(directory + 'ising_model_cv.png')

# %%
