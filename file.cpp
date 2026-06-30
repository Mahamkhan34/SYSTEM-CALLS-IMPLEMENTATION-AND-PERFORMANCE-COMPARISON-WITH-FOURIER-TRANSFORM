
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <chrono>
using namespace std;

int main() {
    auto start = chrono::high_resolution_clock::now();   // start time

    int fd = open("input.txt", O_RDONLY);

    if(fd < 0) {
        cout << "Error opening file\n";
        return 1;
    }

    char buffer[100];
    read(fd, buffer, sizeof(buffer));

    close(fd);

    auto end = chrono::high_resolution_clock::now();   // end time

    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);

    cout << "Data: " << buffer << endl;
    cout << "Time taken: " << duration.count() << " us " << endl;

    return 0;
}
