/* Abe Kesting
 * Lab week 10
 * 11/6/24
 * Section 111
 */
// info.c

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    struct timespec time;
    int error = clock_gettime(CLOCK_REALTIME, &time);
    if (error) {
        exit(1);
    }
    struct tm loctime;
    localtime_r(&time.tv_sec,&loctime);//needed to use localtime to account for time zones and stuff
    printf("time: %d:%02d:%d:%ld\n",loctime.tm_hour,loctime.tm_min,loctime.tm_sec,time.tv_nsec);

    struct utsname name;
    error = uname(&name);
    if (error) {
        exit(1);
    }
    printf("network name:%s\n",name.nodename);


    printf("system name: %s\n",name.sysname);

    printf("os version: %s, release: %s\n",name.version,name.release);

    printf("hardware type: %s\n", name.machine);

    printf("processors: %d\n", get_nprocs());

    long page_size = sysconf(_SC_PAGE_SIZE);
    long num_pages = sysconf(_SC_PHYS_PAGES);
    long av_pages = sysconf(_SC_AVPHYS_PAGES);
    printf("number of bytes in physical memory %ld\n",page_size*num_pages);
    printf("number of bytes available %ld\n",page_size*av_pages);



    return 0;
}