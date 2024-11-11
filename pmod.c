/* Abe Kesting
 * Lab week 10
 * 11/6/24
 * Section 111
 */

// pmod.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char* argv[]) {

    nice(-10); //positive number increments the priority, which makes the os favor the process less
    struct timespec time;
    time.tv_sec=1;
    time.tv_nsec = 837272638L;
    struct timespec rm;
    rm.tv_sec=0;
    rm.tv_nsec=0;
    int error = nanosleep(&time, &rm);
    if (error==-1) {
        printf("interrupted, %li ns remaining\n", rm.tv_nsec);
    }
    printf("done\n");

    return 0;
}