//
// percolation simulation

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <iostream>
#include <vector>

#define N_grid 250
#define N_ITERATIONS 100

int grid[N_grid][N_grid];  // holding the particles (perconalted sites)
int cluster_number[N_grid][N_grid];  // hold the cluster number
// does not belong to any cluster == -1

int actual_cluster;

// double p;  /// probability of picking the site

FILE *moviefile;

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
  // printf("Filled up the system.Ended up with %d particles \n", N_particles);
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

void write_cmovie(int t) {
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

int findMaxClusterSize() {
  if (!actual_cluster) return 0;
  std::vector<int> clusters(actual_cluster, 0);

  for (int i = 0; i < N_grid; i++) {
    for (int j = 0; j < N_grid; j++) {
      if (cluster_number[i][j] >= 1) {
        clusters[cluster_number[i][j] - 1]++;
      }
    }
  }
  return *std::max_element(std::begin(clusters), std::end(clusters));
}

int hasSpanningCluster() {
  for (int i = 0; i < N_grid; i++) {
    for (int j = 0; j < N_grid; j++) {
      if ((cluster_number[0][i] != -1 &&
           cluster_number[0][i] == cluster_number[N_grid - 1][j]) ||
          (cluster_number[i][0] != -1 &&
           cluster_number[i][0] == cluster_number[j][N_grid - 1])) {
        return 1;
      }
    }
  }
  return 0;
}

// int main(int argc, const char *argv[]) {
int main() {
  // printf("Percolation calculation \n");

  // probability of occupying a given site: p
  // p = 0.6;

  moviefile = fopen("perk.mvi", "wb");
  std::cout << "n_grid,p,avg_max_cluster,probability_spanning_cluster"
            << std::endl;
  for (double i = 0; i < 1.01; i += 0.01) {
    double p = i;
    double avg_max_cluster = 0.0;
    double spanning_probability = 0.0;
    for (int t = 0; t < N_ITERATIONS; t++) {
      // srand(1446742268);
      int seed = (int)time(NULL) + t * 10;
      // printf("%d seed=%d\n", t, seed);
      srand(seed);

      initialize_system();
      fill_system_with_probability(p);

      clusterize_system();
      write_cmovie(t);

      // right here I can calculate statistics
      // - size of the largest cluster (average)
      avg_max_cluster += findMaxClusterSize();
      // - probability of a spanning cluster in the system (probability of
      // percolation)
      spanning_probability += hasSpanningCluster();
    }
    avg_max_cluster /= N_ITERATIONS;
    spanning_probability /= N_ITERATIONS;

    std::cout << N_grid << "," << p << "," << avg_max_cluster << ","
              << spanning_probability << std::endl;
  }

  fclose(moviefile);

  return 0;
}
