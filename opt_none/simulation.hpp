// Simulation Header, with definition to the Simulation class.
// TODO: Extend documentation


#ifndef MD_OPTNONE_SIMULATION_H_
#define MD_OPTNONE_SIMULATION_H_

#include <cstdlib>
#include <cmath>
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>

namespace MD {
    // Constant particle density for each simulation
    #define PARTICLE_DENSITY (800.0 / (60.0 * 60.0))
    #define MINIMUM_DISTANCE (0.25)

    // Simulation class
    // Defines and control simulation
    class Simulation {
        public:


            // Constructor method
            Simulation(bool t_verbose, int t_n_particles=800,
                       double t_dt=0.001,
                       double t_particle_particle_screening_length=4.0,
                       double t_particle_driving_force=0.5);
            

            // public methods

            
            // Runs simulation, based on the class' parameters
            void runSimulation(int t_total_time=100000, int t_echo_time=1000,
                               int t_movie_time=100);


        private:
            // simulation variables
            bool m_verbose;
            int m_n_particles, m_time = 0;
            double m_dt, m_sx, m_sy, m_half_sx, m_half_sy,
                   m_particle_particle_screening_length,
                   m_particle_driving_force;
            std::vector<double> m_particle_x, m_particle_y, m_particle_fx,
                m_particle_fy, m_particle_direction;
            std::vector<int> m_particle_color;

            // file output variables
            std::ofstream m_moviefile;
            
            // timing variables
            using clock_t = std::chrono::high_resolution_clock;
            using second_t = std::chrono::duration<double, std::ratio<1> >;
            std::chrono::time_point<clock_t> m_time_begin, m_time_end;

            // private methods


            // calculates the shortest distance between 2 points in a PBC configuration
            // only used in the random deposition check which happens once at initialization
            // so this is not so time crucial left the square root inside
            double distanceFoldedPBC(double x0, double y0, double x1,
                                     double y1);


            // calculates the shortest distance squared between 2 points in a PBC configuration
            // this is squared because I want to save on sqrt with the lookup table
            // also used by the Verlet rebuild flag check where I check how much a particle moved
            void distanceFoldedPBCSquared(double x0, double y0, double x1,
                                          double y1, double *r2_return,
                                          double *dx_return, double *dy_return);


            // fold back the particle into the PBC simulation box
            // assumes it did not jump more than a box length
            // if it did the simulation is already broken anyhow
            void foldParticleBackPBC(int i);


            // calculates external forces on each particle
            void calcExternalForcesOnParticles();


            // calculates pairwise forces between particles
            void calcPairwiseForces();


            // moves the particles one time step
            void moveParticles();

            // Writes current scenario to .mvi file as a new frame
            void writeCMovieFrame();
    };
}

#endif
