#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <chrono>
using namespace std;

int main() {
    auto start = chrono::high_resolution_clock::now();

    int fd = open("input.txt", O_RDONLY);

    auto end = chrono::high_resolution_clock::now();

    if(fd < 0)
        cout << "Error opening file\n";
    else
        cout << "File opened successfully\n";

    cout << "Time: " << chrono::duration_cast<chrono::microseconds>(end-start).count() << " us\n";

    close(fd);
    return 0;
}
