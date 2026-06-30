#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

int main() {
    struct timespec s, e;
    clock_gettime(CLOCK_MONOTONIC, &s);
    pid_t pid = fork();
    if (pid == 0) { exit(0); }
    else { wait(NULL); }
    clock_gettime(CLOCK_MONOTONIC, &e);
    long us = (e.tv_sec - s.tv_sec) * 1000000L + (e.tv_nsec - s.tv_nsec) / 1000L;
    printf("wait() time: %ld us\n", us);
    return 0;
}
