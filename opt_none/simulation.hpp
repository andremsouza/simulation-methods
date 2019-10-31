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


            double distanceFoldedPBC(double x0, double y0, double x1,
                                     double y1);
            

            void distanceFoldedPBCSquared(double x0, double y0, double x1,
                                          double y1, double *r2_return,
                                          double *dx_return, double *dy_return);
            

            void foldParticleBackPBC(int i);
            

            void calcExternalForcesOnParticles();


            void calcPairwiseForces();


            void moveParticles();


            void writeCMovieFrame();
    };
}

#endif
