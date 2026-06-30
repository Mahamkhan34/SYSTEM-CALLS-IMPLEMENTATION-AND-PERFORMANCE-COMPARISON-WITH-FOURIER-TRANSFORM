#include <stdio.h>
#include <sys/stat.h>
#include <time.h>

int main() {
    struct timespec s, e;
    clock_gettime(CLOCK_MONOTONIC, &s);
    mode_t old = umask(022);
    clock_gettime(CLOCK_MONOTONIC, &e);
    umask(old);
    long us = (e.tv_sec - s.tv_sec) * 1000000L + (e.tv_nsec - s.tv_nsec) / 1000L;
    printf("umask() time: %ld us\n", us);
    return 0;
}
