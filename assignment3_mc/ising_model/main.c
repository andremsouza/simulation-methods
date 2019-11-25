
//  main.c
//  ising_model


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define L_max 100

int L_spin; //N = L x L side of the lattice
int N_spin; // number of spins
int spin[L_max][L_max];

int t; //time
double T; //Temperature
long int N_steps_per_T; // this many MC steps for each Temperature

long int step;
double M_avg,M2_avg,E_avg,E2_avg;
long int N_rej; //how many rejections happened

FILE *outfile;
FILE *moviefile;

void statistics_initialization();
void spin_initialization();
void write_cmovie();
void write_out_result();

void statistics_initialization()
{
    M_avg = 0.0;
    M2_avg = 0.0;
    E_avg = 0.0;
    E2_avg = 0.0;
    N_rej = 0;
}

void spin_initialization()
{
    int i,j;
    int pos,neg;
    
    pos = 0;
    neg = 0;
    
    for(i=0;i<L_spin;i++)
        for(j=0;j<L_spin;j++)
            {
            
            //we can start from this initial condition:
            //all spins pointing in random directions
            //this is a high energy state good for high temperatures
            //starting from this at low T might get the system stuck
            //in high energy configurations for a long transient
            //better not start the system like this
            /*
            if ( (rand()/(RAND_MAX+1.0)) < 0.5)
                {
                    spin[i][j] = 1;
                    pos++;
                }
            else
                {
                    spin[i][j] = -1;
                    neg++;
                }
             */
                
            //uniform initialization
            //All spins pointing in one direction. This is a low energy
            //state, that is good for low temperatures. When starting
            //at high temperatures the system will have a transient to
            //higher energy states but this will be facilitated by the
            //possible flips at high temperatures (the system will not
            //get stuck in the high energy configuration)
            spin[i][j] = +1;
            pos++;
            }
    
    printf("Initialization is complete\n");
    printf("pos = %d neg = %d\n",pos,neg);
    
    /*
    //write out the spin configuration to a file
    if (T==0.1)
    for(i=0;i<L_spin;i++)
        for(j=0;j<L_spin;j++)
            if (spin[i][j]==1) fprintf(outfile,"%d %d\n",i,j);
     */
}

//how much the energy would change if I flipped this spin
int Energy_function_for_one_spin(int fi,int fj)
{
    int ni,nj; //neighbor,we have 4 neighbors in total
    int i;
    
    int delta = 0;
    
    for(i=0;i<4;i++)
        {

            switch(i)
                {
                    case 0: {ni = fi - 1; nj = fj; break;} // left
                    case 1: {ni = fi + 1; nj = fj; break;} // right
                    case 2: {ni = fi;     nj = fj + 1; break;} //up
                    case 3: {ni = fi;     nj = fj - 1; break; } //down
                    default: {
                                ni=fi; nj=fj;
                                printf("You should never get to this line!!!\n");
                             }
                }
            
            //PBC periodic boundary conditions fold-back
            if (ni<0) ni = ni + L_spin;
            if (ni>=L_spin) ni = ni - L_spin;
            if (nj<0) nj = nj + L_spin;
            if (nj>=L_spin) nj = nj - L_spin;
            
            //change in the energy
            delta = delta - spin[fi][fj]*spin[ni][nj];
            
        }
    //delta is how much the energy would chage if I flipped spin
    //on the position fi,fj in the lattice
    
    return delta;
}

int delta_E(int fi,int fj)
{
    int dE;
    
    dE = - 2 * Energy_function_for_one_spin(fi,fj);

    return dE;
}


//flips spin (on the position: to_be_flipped_i,to_be_flipped_j)
void flip_spin(to_be_flipped_i,to_be_flipped_j)
{
    spin[to_be_flipped_i][to_be_flipped_j] = - spin[to_be_flipped_i][to_be_flipped_j];
}

void calculate_statistics()
{

    double M,M2,E,E2;
    int i,j;

    M = 0.0;//magnetization
    E = 0.0;//energy
    
    //go over all spins sum up
    //the magnetization and energy
    for(i=0;i<L_spin;i++)
        for(j=0;j<L_spin;j++)
            {
                M = M + (double)spin[i][j];
                E = E + (double)Energy_function_for_one_spin(i,j);
            }
    
    //square of M and E
    M2 = M * M;
    E2 = E * E;
    
    M_avg += M/(double)N_steps_per_T;
    M2_avg += M2/(double)N_steps_per_T;
    E_avg  += E/(double)N_steps_per_T;
    E2_avg += E2/(double)N_steps_per_T;

}

void run_for_fixed_T()
{
    int to_be_flipped_i,to_be_flipped_j;
    int dE;
    double p,r;
    
    for(step=0;step<N_steps_per_T;step++)
        {
            //pick the spin at random
            to_be_flipped_i = (int)floor((double)L_spin * rand()/(RAND_MAX+1.0));
            to_be_flipped_j = (int)floor((double)L_spin * rand()/(RAND_MAX+1.0));
            
            //calculate the delta E that this spin flip will cause
            dE = delta_E(to_be_flipped_i,to_be_flipped_j);
            
            //printf("dE = %d ",dE);
            
            //Metropolis MC rejection
            if (dE<=0)  {
                        //if the energy is lowered then ALWAYS make the step
                        //flip the spin if that lowers the energy
                        flip_spin(to_be_flipped_i,to_be_flipped_j);
                        }
            
            else        {
                        //the energy is  raised by this flip
                        //there is a probability (Boltzmann factor)
                        //that I will accept this move
                        //this is the probability that I accept the move:
                        p = exp(-(double)dE/(double)T); //between (0..1)
                
                        r = rand()/(RAND_MAX+1.0); //random number from 0..1
                
                        if (r<p) flip_spin(to_be_flipped_i,to_be_flipped_j);
                                     //this is when we do the flip
                        else N_rej++;//otherwise I reject the move
                    }
            
            //take the SAME OLD state again if there was no spin flip
            //so calculate the statistics again for the state (even if no flip happened)
            //this is how I handle the rejection
            
            calculate_statistics();
            
            //write to the movie file
            if (t%10000==0) write_cmovie();
            t++;
        }
    
}

void write_out_result()
{
double chi, cv;

    M_avg = M_avg / N_spin;
    E_avg = E_avg / N_spin;
    M2_avg = M2_avg / N_spin / N_spin;
    E2_avg = E2_avg / N_spin / N_spin;

    
    chi  = (M2_avg - M_avg * M_avg)/T;
    cv  = (E2_avg - E_avg * E_avg)/N_spin/T/T;

    
    //printf("T = %lf |M| = %lf <M>*<M> = %lf <M^2> = %lf chi = %lf \n",T,fabs(M_avg),M_avg*M_avg,M2_avg,chi);
    
    printf("T = %lf |M| = %lf chi = %lf\n",T,fabs(M_avg),chi);

}


void write_cmovie()
{
    int i,j;
    float floatholder;
    int intholder;
    
    intholder = N_spin;
    fwrite(&intholder,sizeof(int),1,moviefile);
    
    intholder = t;
    fwrite(&intholder,sizeof(int),1,moviefile);
  
    for(i=0;i<L_spin;i++)
        for(j=0;j<L_spin;j++)
        {
            if (spin[i][j]==-1) intholder = 2; //color of spin
            else intholder = 3;
            fwrite(&intholder,sizeof(int),1,moviefile);
            intholder = i*L_spin+j;            //spin ID
            fwrite(&intholder,sizeof(int),1,moviefile);
            floatholder = (float)i;
            fwrite(&floatholder,sizeof(float),1, moviefile);
            floatholder = (float)j;
            fwrite(&floatholder,sizeof(float),1,moviefile);
            floatholder = 1.0;//cum_disp, cmovie format
            fwrite(&floatholder,sizeof(float),1,moviefile);
        }
}

int main(int argc, const char * argv[])
{
    printf("Ising model simulation\n");
    
    outfile = fopen("ising_data_T21.dat","wt");
    moviefile = fopen("ising_movie_T21.dat","wb");
    
    srand((int)time(NULL));
    
    L_spin = 50;
    N_spin = L_spin * L_spin; //50x50 lattice of spins
    
    N_steps_per_T = 1000000;

    t = 0;
    T = 0.5;
    //initial temperature, don't set it to 0.0
    //or re-write the division by temperature if you do
    
    spin_initialization();
    printf("Run started\n");
    while(T<=4.0)
        {
        //the reason the spin initialization is not in the loop
        //is that subsequent temperatures have similar states in
        //the set of states we want to generate for them
        
        statistics_initialization();
        run_for_fixed_T();
        write_out_result();
        
        //increase the Temperature here
        T = T + 0.05;
        }
    
    fclose(outfile);
    fclose(moviefile);
    return 0;
}
