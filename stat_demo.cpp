#include <iostream>
#include <sys/stat.h>
#include <chrono>
using namespace std;
int main() {
    auto start = chrono::high_resolution_clock::now();

    struct stat info;
    if(stat("input.txt", &info) == 0) {
        cout << "File size: " << info.st_size << " bytes\n";
        cout << "File inode: " << info.st_ino << endl;
    } else {
        cout << "Error\n";
    }

    auto end = chrono::high_resolution_clock::now();
    cout << "Time: " << chrono::duration_cast<chrono::microseconds>(end-start).count() << " us\n";
}

