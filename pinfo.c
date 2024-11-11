/* Abe Kesting
 * Lab week 10
 * 11/6/24
 * Section 111
 */
// pinfo.c
#define _GNU_SOURCE
#include <stdio.h>
#include <sched.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/resource.h>


int main(int argc, char* argv[]) {
    pid_t pid = getpid(); //gets the pid of this program
    if (argc > 1) {
        pid = (pid_t)atoi(argv[1]);//overrwrite if command line has one
    }
    
    errno = 0;

    int priority = getpriority(PRIO_PROCESS, pid);
    if (errno) { //can reasonably return -1, so check errno
        printf("Error getting priority\n");
        exit(1);
    }
    
    printf("Priority of %d: %d\n",pid, priority);
    int schedule = sched_getscheduler(pid);
    if (schedule < 0) {
        perror("Error finding schedule");
        exit(1);
    }
    char* name;
    switch (schedule) { //different schedules found on man page
        case SCHED_OTHER :
            name = "other";
            break;
        case SCHED_BATCH :
            name = "batch";
            break;
        case SCHED_IDLE :
            name = "idle";
            break;
        case SCHED_FIFO :
            name = "fifo";
            break;
        case SCHED_RR :
            name = "round-robin";
            break;
        default :
            name = "unknown";
    }
    printf("Schedule is: %s\n", name);


    return 0;
}