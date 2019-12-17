
//  main.cpp
//  softplot
//  Simulation Methods course, 2018
//  First Assignment: Molecular Dynamics (Brownian Dynamics) Simulation
//  Visualization part (needs the movie file copid into its directory)

// The OpenGL libraries, make sure to include the GLUT and OpenGL frameworks

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "globaldata.h"
#include "drawing.h"


int main(int argc, char **argv)
{

    initialize_global_data();
    
    read_moviefile_data();
    
    init_glut();
    init_OpenGl();

    start_main_loop_glut();
    
    return 0;
}
