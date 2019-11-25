//
//  main.c
//  randomsampling
//
//  Created by Andras Libal on 10/24/17.
//  Copyright © 2017 Andras Libal. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double x,y,x_new,y_new;
int N_inside;
int N_total;
int N_thrown;
double theta;

FILE *coords;

int main(int argc, const char * argv[]) {

    N_inside = 0;
    N_total = 10000000;
    N_thrown = 0;
    
    x = 10.0;
    y = 10.0;
    
    coords = fopen("coordinates.dat","wt");
    
    for(int i=0;i<N_total;i++)
    {
   
     
    //direct sampling
    //square is 0..20 x 0..20
    
    //x = 20.0*rand()/(RAND_MAX+1.0);
    //y = 20.0*rand()/(RAND_MAX+1.0);
    
    //Markov chain sampling
    
    theta = 2.0*3.141592*rand()/(RAND_MAX+1.0);
   
    x_new = x + 1.0*cos(theta);
    y_new = y + 1.0*sin(theta);
    
    if ( (x_new>=0)&&(x_new<=20.0)
         &&(y_new>=0)&&(y_new<=20.0))
            {
            //this is when I am inside the box
            x = x_new;
            y = y_new;
            
            }

    //in the else, the OLD point is used AGAIN
    //this is rejection handling
    fprintf(coords,"%lf %lf\n",x,y);
    
    N_thrown++;

    if (x*x+y*y<20.0*20.0) N_inside++;
        
    }
    fclose(coords);
    printf("My approximation for pi = %lf\n",
        4.0*N_inside/(double)N_thrown);

    return 0;
}
