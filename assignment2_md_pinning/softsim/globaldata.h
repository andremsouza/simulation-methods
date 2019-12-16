
//  globaldata.h
//  Simulation Methods course, 2018
//  First Assignment: Molecular Dynamics (Brownian Dynamics) Simulation

#ifndef globaldata_h
#define globaldata_h

#include <stdio.h>

struct global_struct
    {
    double SX, SY;
    double halfSX,halfSY;
    
    int     N_particles;
    
    double  *particle_x;                        //particle x position
    double  *particle_y;                        //particle y position
    double  *particle_fx;                       //particle total force x direction
    double  *particle_fy;                       //particle total force y direction
    int     *particle_color;                    //particle color
    double  *particle_direction;                //direction of external force

    double  *stat_fx; //statistics on the x direction velocity
        
    int     N_pinningsites;
        
    double *pinning_x;//center of the pinning site x
    double *pinning_y;//center of the pinning site y
    double *pinning_R;//Radius of the pinning site
    double *pinning_fmax;//maximum force at the edge of the pinning site
    
    double pinning_Radius; //if all pinning sites are the same, this is R
    double pinning_Radius2;//square of the previous quantity
    double pinning_force;  //and this is fmax
    
    double  particle_driving_force;             //external driving force
    double  particle_driving_force_max;
    double  particle_particle_screening_length;  //inter-partcile force screening length
    
    double dt;          //simulation step length
    
    int total_time;     //total running time
    int echo_time;      //echo to screen
    int movie_time;     //write to file
    int stat_time;      //write to statistics file
    int time;           //current time step
    
    FILE *moviefile;
    FILE *statisticsfile;
        
    double Verlet_cutoff_distance;
    double Verlet_cutoff_distance_squared;
    double Verlet_intershell_squared;
    
    int N_Verlet;
    int N_Verlet_max; //initial allocation + later, longest allocation
    int *Verletlisti;
    int *Verletlistj;
    int flag_to_rebuild_Verlet;
    
    double *particle_dx_so_far;
    double *particle_dy_so_far;
    
    };

extern struct global_struct global;

#endif /* globaldata_h */
