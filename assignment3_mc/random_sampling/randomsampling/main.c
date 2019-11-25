//
//  main.c
//  randomsampling
//
//  Monte Carlo Simulation
//  Sampling Points inside a circle inside a square
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double x,y,x_new,y_new;//position of the stone
long int N_inside;
long int N_total;
long int N_thrown;
double theta;

FILE *coords, *coords_inside;

int main(int argc, const char * argv[]) {
    
    printf("Approximate Pi\n");
    N_inside = 0;
    N_total = 100000000;
    N_thrown = 0;
    
    //starting position for the Markov chain sampling
    
    x = 10.0;
    y = 10.0;
    
    coords = fopen("coordinates.txt","wt");
    coords_inside = fopen("coordinates_inside.txt","wt");
    for(int i=0;i<N_total;i++)
    {
    //direct sampling
    //square is 0..20 x 0..20
   /*
    x = 20.0 * rand()/(RAND_MAX+1.0);
    y = 20.0 * rand()/(RAND_MAX+1.0);
    
    fprintf(coords,"%lf %lf\n",x,y);
    
    if (x*x + y*y < 20.0*20.0) // it is inside the circle
        {
        N_inside++;
        fprintf(coords_inside,"%lf %lf\n",x,y);
        }
    N_thrown++;
    }
    
    */
    
    //Markov chain sampling
    //pick the angle randomly
    
    theta = 2.0 * 3.141592 * rand()/(RAND_MAX+1.0);
    
   //make the throw (lenght is 1.0)
    x_new = x + 1.0 * cos(theta);
    y_new = y + 1.0 * sin(theta);
    
    //check if the stone is inside the square
    if ( (x_new>=0)&&(x_new<=20.0)
         &&(y_new>=0)&&(y_new<=20.0))
            {
            //this is when I am inside the box
            x = x_new;
            y = y_new;
            
            
            
            
            
            }
    //else - I GOT OUTSIDE THE SQUARE
    //I PRETEND NOTHING HAPPENED (this is how I handle REJECTION)
    //this is how I handle rejection BADLY
    
    
    //how to handle it well:
    fprintf(coords,"%lf %lf\n",x,y);
    N_thrown++;
    
    if (x*x+y*y<20.0*20.0)
    {
    N_inside++;
    fprintf(coords_inside,"%lf %lf\n",x,y);
    
    
    
    //handling of the new coordinates
    //got new coordinates OR OLD COORDINATES that are good!!!
    
    }
    
    //correct rejection handling
    //if a stone went out I use the SAME OLD x,y AGAIN
    //fprintf(coords,"%lf %lf\n",x,y);
    //N_thrown++;
    
    
    
    }
    
    fclose(coords);
    fclose(coords_inside);
    printf("My approximation for pi = %lf\n",
        4.0 * N_inside/(double)N_thrown);

    // insert code here...
    return 0;
}
