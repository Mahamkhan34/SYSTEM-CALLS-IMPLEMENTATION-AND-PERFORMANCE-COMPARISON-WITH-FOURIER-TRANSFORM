#include <chrono>
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
using namespace std;

auto start = chrono::high_resolution_clock::now();int main() {
    int fd = open("input.txt", O_RDONLY);

    if(fd < 0) {
        cout << "Error opening file\n";
        return 1;
    }

    int size = 100;

    char* data = (char*) mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);

    if(data == MAP_FAILED) {
        cout << "mmap failed\n";
        return 1;
    }

    cout << "File content using mmap:\n";
    cout << data << endl;

    munmap(data, size);
    close(fd);
auto end = chrono::high_resolution_clock::now();
auto duration = chrono::duration_cast<chrono::microseconds>(end - start);

cout << "Time taken: " << duration.count() << " us " << endl;
    return 0;
}
