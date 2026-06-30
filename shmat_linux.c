
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>

int main() {
    struct timespec s, e;
    key_t key = ftok("/tmp", 65);
    int shmid = shmget(key, 1024, 0666|IPC_CREAT);
    clock_gettime(CLOCK_MONOTONIC, &s);
    void *addr = shmat(shmid, NULL, 0);
    clock_gettime(CLOCK_MONOTONIC, &e);
    long us = (e.tv_sec - s.tv_sec) * 1000000L + (e.tv_nsec - s.tv_nsec) / 1000L;
    printf("shmat() time: %ld us\n", us);
    shmdt(addr);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}
