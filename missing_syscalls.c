#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>

// Helper: returns elapsed microseconds
long get_time_us(struct timespec start, struct timespec end)
{
    return (end.tv_sec - start.tv_sec) * 1000000L +
           (end.tv_nsec - start.tv_nsec) / 1000L;
}

int main()
{
    struct timespec start, end;
    printf("%-12s | %-20s\n", "System Call", "Linux Time (us)");
    printf("-------------|---------------------\n");

    // ─── 1. wait() ───────────────────────────────────────────
    clock_gettime(CLOCK_MONOTONIC, &start);
    pid_t pid = fork();
    if (pid == 0)
    {
        exit(0);
    } // child exits immediately
    else
    {
        wait(NULL);
    } // parent waits
    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("%-12s | %ld\n", "wait()", get_time_us(start, end));

    // ─── 2. shmat() ──────────────────────────────────────────
    key_t key = ftok("/tmp", 65);
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    clock_gettime(CLOCK_MONOTONIC, &start);
    void *shmaddr = shmat(shmid, NULL, 0);
    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("%-12s | %ld\n", "shmat()", get_time_us(start, end));
    shmdt(shmaddr);
    shmctl(shmid, IPC_RMID, NULL);

    // ─── 3. chown() ──────────────────────────────────────────
    // Create a temp file first
    int fd = open("/tmp/test_chown.txt", O_CREAT | O_WRONLY, 0644);
    close(fd);
    clock_gettime(CLOCK_MONOTONIC, &start);
    chown("/tmp/test_chown.txt", getuid(), getgid());
    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("%-12s | %ld\n", "chown()", get_time_us(start, end));
    remove("/tmp/test_chown.txt");

    // ─── 4. umask() ──────────────────────────────────────────
    clock_gettime(CLOCK_MONOTONIC, &start);
    mode_t old = umask(022);
    clock_gettime(CLOCK_MONOTONIC, &end);
    umask(old); // restore
    printf("%-12s | %ld\n", "umask()", get_time_us(start, end));

    return 0;
}