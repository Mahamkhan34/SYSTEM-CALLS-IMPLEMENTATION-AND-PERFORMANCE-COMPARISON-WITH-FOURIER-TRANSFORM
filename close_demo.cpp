#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <chrono>
using namespace std;

int main() {
    int fd = open("input.txt", O_RDONLY);

    auto start = chrono::high_resolution_clock::now();

    close(fd);

    auto end = chrono::high_resolution_clock::now();

    cout << "File closed\n";
    cout << "Time: " << chrono::duration_cast<chrono::microseconds>(end-start).count() << " us\n";

    return 0;
}
