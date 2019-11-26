//
//  main.c
//  randomsampling
//
//  Monte Carlo Simulation
//  Sampling Points inside a circle inside a square
//

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double x, y, x_new, y_new;  // position of the stone
long int N_inside;
long int N_total;
long int N_thrown;
double theta;

FILE *coords, *coords_inside;

int main(int argc, const char *argv[]) {
  if (argc != 2) {
    fprintf(stdout, "usage: main N_total\n");
    exit(1);
  }
  // printf("Approximate Pi\n");
  N_inside = 0;
  N_total = atoi(argv[1]);
  N_thrown = 0;

  // starting position for the Markov chain sampling

  x = 10.0;
  y = 10.0;

  coords = fopen("coordinates.txt", "wt");
  coords_inside = fopen("coordinates_inside.txt", "wt");
  for (int i = 0; i < N_total; i++) {
    // direct sampling
    // square is 0..20 x 0..20

    x = 20.0 * rand() / (RAND_MAX + 1.0);
    y = 20.0 * rand() / (RAND_MAX + 1.0);

    fprintf(coords, "%lf %lf\n", x, y);

    if (x * x + y * y < 20.0 * 20.0)  // it is inside the circle
    {
      N_inside++;
      fprintf(coords_inside, "%lf %lf\n", x, y);
    }
    N_thrown++;
  }

  fclose(coords);
  fclose(coords_inside);
  // printf("My approximation for pi = %lf\n", 4.0 * N_inside /
  // (double)N_thrown);
  fprintf(stdout, "%ld,%lf\n", N_total, 4.0 * N_inside / (double)N_thrown);

  // insert code here...
  return 0;
}
