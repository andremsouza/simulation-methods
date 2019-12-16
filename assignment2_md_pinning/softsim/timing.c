

#include <stdio.h>
#include "timing.h"
#include "globaldata.h"

#ifdef __MACH__
#include <sys/time.h>

//clock_gettime is not implemented on OSX
//it seems like ti is now
/*
int clock_gettime(int clk_id, struct timespec* t) {
    struct timeval now;
    int rv = gettimeofday(&now, NULL);
    if (rv) return rv;
    t->tv_sec  = now.tv_sec;
    t->tv_nsec = now.tv_usec * 1000;
    return 0;
}

#define CLOCK_REALTIME 0 
#define CLOCK_MONOTONIC 0
*/
#endif

struct timespec program_start_time;
struct timespec program_finish_time;

void get_starting_time()
{
clock_gettime(CLOCK_MONOTONIC, &program_start_time);
}


void get_finishing_time()
{
clock_gettime(CLOCK_MONOTONIC, &program_finish_time);
}


void echo_running_time()
{
double time_expired;
time_t time_endtime;
struct tm *timeinfo;

time_expired  = program_finish_time.tv_sec - program_start_time.tv_sec + (program_finish_time.tv_nsec - program_start_time.tv_nsec)*1e-9;
time(&time_endtime);
timeinfo = localtime(&time_endtime);

printf("Run finished on: %s",asctime(timeinfo));
printf("Program running time was: %.2lf seconds\n",time_expired);
}
