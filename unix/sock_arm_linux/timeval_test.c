#include <time.h>
#include <stdio.h>
#include <stdlib.h>

float
calctimeval(struct timeval start,
            struct timeval end)
{
    float s;
    s = 1000000 * ( end.tv_sec - start.tv_sec ) + end.tv_usec - start.tv_usec;
    s /= 1000000;
    return s;
}

int
main(int argc, char *argv[])
{
    struct timeval start, end;
    float second;
    gettimeofday(&start, NULL);
    sleep(1);
    gettimeofday(&end, NULL);
    second = calctimeval(start, end);
    printf ("timeval: %f\n", second);
    return 0;
}

