// Simulation Methods course, 2019
// First Assignment: Molecular Dynamics (Brownian Dynamics) Simulation
//
// We are simulating a 2D system of particles moving in a PBC box
// the particles have an external driving force acting on them (to the left or
// right) they also have particle-particle repulsion (screened Coulomb type
// force)
//
// a) Run the system without optimization for different system sizes
// b) Run the system with Verlet optimization for different system sizes
// c) Run the system with Verlet + grid optimization for different system sizes
//
// Present:
// - a movie file with a dense system running for a long time
// - the running time vs the system size for the three cases on the same graph
// - be able to answer simple questions about the code probing your
//   understanding of the code and the simulation

#include <cstdlib>
#include <cstring>
#include <iostream>
#include "simulation.hpp"

using namespace std;

// Main function. Runs simulation with default arguments.
int main(int argc, char *argv[]) {
  // Check number of arguments for the main program
  if (argc != 9) {
    cout << "usage: main VERBOSE_BOOL N_PARTICLES DT "
            "PARTICLE_PARTICLE_SCREENING_LENGTH PARTICLE_DRIVING_FORCE "
            "TOTAL_TIME ECHO_TIME MOVIE TIME"
         << endl;
    exit(1);
  }

  // Get arguments from command-line
  const bool verbose = !((strcmp(argv[1], "1") && strcmp(argv[1], "true")));
  const int n_particles = atoi(argv[2]);
  const double dt = atof(argv[3]);
  const double particle_particle_screening_length = atof(argv[4]);
  const double particle_driving_force = atof(argv[5]);
  const int total_time = atoi(argv[6]);
  const int echo_time = atoi(argv[7]);
  const int movie_time = atoi(argv[8]);

  // Output general information
  cout << "Simulation Methods Course, 2019" << endl;
  cout << "#1 Assignment Molecular Dynamics (Brownian Dynamics) simulation"
       << endl;
  cout << "Unoptimized version (slowest)" << endl;

  // Initialize and run simulation
  MD::Simulation sim(verbose, n_particles, dt,
                     particle_particle_screening_length,
                     particle_driving_force);
  sim.runSimulation(total_time, echo_time, movie_time);

  return 0;
}
