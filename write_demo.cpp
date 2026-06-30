#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <chrono>
using namespace std;

int main() {
    auto start = chrono::high_resolution_clock::now();

    int fd = open("output.txt", O_WRONLY | O_CREAT, 0644);

    const char* data = "Hello from write!";
    write(fd, data, 18);

    auto end = chrono::high_resolution_clock::now();

    cout << "Data written to file\n";
    cout << "Time: " << chrono::duration_cast<chrono::microseconds>(end-start).count() << " us\n";

    close(fd);
    return 0;
}
