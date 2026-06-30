#include <iostream>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <chrono>
using namespace std;

int main() {
    int fd = open("input.txt", O_RDONLY);

    char* data = (char*) mmap(NULL, 100, PROT_READ, MAP_PRIVATE, fd, 0);

    auto start = chrono::high_resolution_clock::now();

    munmap(data, 100);

    auto end = chrono::high_resolution_clock::now();

    cout << "Memory unmapped\n";
    cout << "Time: " << chrono::duration_cast<chrono::microseconds>(end-start).count() << " us\n";

    close(fd);
    return 0;
}
