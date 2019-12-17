//
// percolation simulation

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N_grid 100

int grid[N_grid][N_grid];  // holding the particles (perconalted sites)
int cluster_number[N_grid][N_grid];  // hold the cluster number
// does not belong to any cluster == -1

int actual_cluster;

// double p;  /// probability of picking the site

FILE *moviefile;
int t;

void initialize_system() {
  int i, j;
  for (i = 0; i < N_grid; i++)
    for (j = 0; j < N_grid; j++) {
      grid[i][j] = 0;             // have not picked any sites
      cluster_number[i][j] = -1;  // nobody is in a cluster
    }
}

void fill_system_with_probability(double p) {
  int i, j;
  double r;
  int N_particles;

  N_particles = 0;

  for (i = 0; i < N_grid; i++)
    for (j = 0; j < N_grid; j++) {
      cluster_number[i][j] = -1;

      r = rand() / (RAND_MAX + 1.0);
      // if r<p, this site will be filled
      if (r < p) {
        grid[i][j] = 1;
        N_particles++;
      }
    }
  printf("Filled up the system.Ended up with %d particles \n", N_particles);
}

void recursive_clusternumber(int i, int j) {
  cluster_number[i][j] = actual_cluster;

  if ((i + 1 < N_grid))
    // find a position to the right of the actual position
    if ((cluster_number[i + 1][j] == -1) && (grid[i + 1][j] == 1))
      recursive_clusternumber(i + 1, j);
  // find a position to the left
  if ((i - 1 >= 0))
    if ((cluster_number[i - 1][j] == -1) && (grid[i - 1][j] == 1))
      recursive_clusternumber(i - 1, j);
  // up
  if ((j + 1 < N_grid))
    if ((cluster_number[i][j + 1] == -1) && (grid[i][j + 1] == 1))
      recursive_clusternumber(i, j + 1);
  // down
  if ((j - 1 >= 0))
    if ((cluster_number[i][j - 1] == -1) && (grid[i][j - 1] == 1))
      recursive_clusternumber(i, j - 1);
}

void clusterize_system() {
  int i, j;

  actual_cluster = 1;

  for (i = 0; i < N_grid; i++)
    for (j = 0; j < N_grid; j++) {
      // filled position, it's not in any cluser
      if ((grid[i][j] == 1) && (cluster_number[i][j] == -1)) {
        // start the recursive algorithm
        // to find everybody connected to this point
        recursive_clusternumber(i, j);
        // the next cluster is going to
        // be a bigger number
        actual_cluster++;
      }
    }
  actual_cluster--;  // to get the actual number of clusters
}

void write_cmovie() {
  int i, j;
  float floatholder;
  int intholder;

  intholder = N_grid * N_grid;
  fwrite(&intholder, sizeof(int), 1, moviefile);

  intholder = t;
  fwrite(&intholder, sizeof(int), 1, moviefile);

  for (i = 0; i < N_grid; i++)
    for (j = 0; j < N_grid; j++) {
      // color the particles based on which
      // cluster they belong to
      if (grid[i][j] == 0)
        intholder = 2;
      else
        intholder = 3 + (cluster_number[i][j] % 10);
      fwrite(&intholder, sizeof(int), 1, moviefile);
      intholder = i * N_grid + j;  // spin ID
      fwrite(&intholder, sizeof(int), 1, moviefile);
      floatholder = (float)i;
      fwrite(&floatholder, sizeof(float), 1, moviefile);
      floatholder = (float)j;
      fwrite(&floatholder, sizeof(float), 1, moviefile);
      floatholder = 1.0;  // cum_disp, cmovie format
      fwrite(&floatholder, sizeof(float), 1, moviefile);
    }
}

int main(int argc, const char *argv[]) {
  printf("Percolation calculation \n");

  // probability of occupying a given site: p
  // p = 0.6;
  double p = 0.6;
  t = 0;

  moviefile = fopen("perk.mvi", "wb");

  for (t = 0; t < 100; t++) {
    // srand(1446742268);
    int seed = (int)time(NULL) + t * 10;
    printf("%d seed=%d\n", t, seed);
    srand(seed);

    initialize_system();
    fill_system_with_probability(p);

    // right here I can calculate statistics
    // - size of the largest cluster (averaged)
    // - probability of a spanning cluster in the system (probability of
    // percolation)

    clusterize_system();
    write_cmovie();
  }

  fclose(moviefile);

  return 0;
}
