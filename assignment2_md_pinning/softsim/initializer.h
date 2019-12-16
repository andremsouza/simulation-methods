//  initializer.h
//  Simulation Methods course, 2018
//  First Assignment: Molecular Dynamics (Brownian Dynamics) Simulation

#ifndef initializer_h
#define initializer_h

#include <stdio.h>
#include <stdlib.h>

void init_simulation(void);
void init_simulation_box(void);

void init_particles(void);
void init_particles_randomly(void);

void init_pinningsites_randomly(void);


void init_files(void);

double distance_folded_PBC(double x0,double y0,double x1,double y1);

#endif /* initializer_h */
