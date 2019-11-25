
//  main.cpp
//  softplot
//  Simulation Methods course, 2018
//  First Assignment: Molecular Dynamics (Brownian Dynamics) Simulation
//  Visualization part (needs the movie file copid into its directory)

// The OpenGL libraries, make sure to include the GLUT and OpenGL frameworks

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "drawing.h"
#include "globaldata.h"

int main(int argc, char **argv) {
  char filename[64];

  // read filename from stdin
  fprintf(stdout, "MVI filename: ");
  fscanf(stdin, "%s", filename);

  initialize_global_data(filename);

  read_moviefile_data();

  init_glut(&argc, argv);
  init_OpenGl();

  start_main_loop_glut();

  return 0;
}
