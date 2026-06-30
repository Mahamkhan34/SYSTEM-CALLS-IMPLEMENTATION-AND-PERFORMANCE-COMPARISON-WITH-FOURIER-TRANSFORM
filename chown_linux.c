
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

int main() {
    struct timespec s, e;
    int fd = open("/tmp/test.txt", O_CREAT|O_WRONLY, 0644);
    close(fd);
    clock_gettime(CLOCK_MONOTONIC, &s);
    chown("/tmp/test.txt", getuid(), getgid());
    clock_gettime(CLOCK_MONOTONIC, &e);
    long us = (e.tv_sec - s.tv_sec) * 1000000L + (e.tv_nsec - s.tv_nsec) / 1000L;
    printf("chown() time: %ld us\n", us);
    remove("/tmp/test.txt");
    return 0;
}
