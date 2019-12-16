

//
//  Simulation Methods course, 2018
//  First Assignment: Molecular Dynamics (Brownian Dynamics) Simulation
//
//  We are simulating a 2D system of particles moving in a PBC box
//  the particles have an external driving force acting on them (to the left or right)
//  they also have particle-particle repulsion (screened Coulomb type force)
//
//  a) Run the system without optimization for different system sizes
//  b) Run the system with Verlet optimization for different system sizes
//  c) Run the system with Verlet + grid optimization for different system sizes
//
//  Present:
//  - a movie file with a dense system running for a long time
//  - the running time vs the system size for the three cases on the same graph
//  - be able to answer simple questions about the code probing your
//    understanding of the code and the simulation

#include <stdio.h>

#include "initializer.h"
#include "running.h"

int main(int argc, const char * argv[])
{
    printf("Simulation Methods Course, 2018\n");
    printf("#1 Assignment Molecular Dynamics (Brownian Dynamics) simulation\n");
    printf("Unpotimized version (slowest)\n");
   
    init_simulation();
    init_simulation_box();

    init_particles();
    init_pinningsites_randomly();
    
    init_files();
    
    run_simulation();
    
    return 0;
}
