#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <chrono>
using namespace std;

int main() {
    auto start = chrono::high_resolution_clock::now();

    int fd = open("input.txt", O_RDONLY);

    char buffer[100];
    read(fd, buffer, sizeof(buffer));

    auto end = chrono::high_resolution_clock::now();

    cout << "Data: " << buffer << endl;
    cout << "Time: " << chrono::duration_cast<chrono::microseconds>(end-start).count() << " us\n";

    close(fd);
    return 0;
}
