import seaborn as sns
import pandas as pd
import matplotlib.pyplot as plt

# sns.set(style="darkgrid")

directory = './assignment1_md/'
df_opt_none = pd.read_csv(directory + "/opt_none/opt_none.csv")
df_opt_none['type'] = 'opt_none'
df_opt_verlet = pd.read_csv(directory + "/opt_verlet/opt_verlet.csv")
df_opt_verlet['type'] = 'opt_verlet'
df_opt_verlet_t = pd.read_csv(
    directory + "/opt_verlet_tabulated/opt_verlet_tabulated.csv")
df_opt_verlet_t['type'] = 'opt_verlet_t'

df = df_opt_none.append(df_opt_verlet.append(
    df_opt_verlet_t, ignore_index=True), ignore_index=True)

# with all three lines
# plt.figure(figsize=(20, 20))
plt.figure()
t = sns.lineplot(x="particle_number", y="time", data=df, hue="type")
plt.savefig(directory + 'graph_all.png')

df = df_opt_verlet.append(df_opt_verlet_t, ignore_index=True)

# with verlet optmization
# plt.figure(figsize=(20, 20))
plt.figure()
t = sns.lineplot(x="particle_number", y="time", data=df, hue="type")
plt.savefig(directory + 'graph_verlet.png')
