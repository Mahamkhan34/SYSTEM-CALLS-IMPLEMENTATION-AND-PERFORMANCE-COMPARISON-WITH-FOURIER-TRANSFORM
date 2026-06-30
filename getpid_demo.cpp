#include <iostream>
#include <unistd.h>
#include <chrono>
using namespace std;
int main() {
    auto start = chrono::high_resolution_clock::now();

    pid_t pid = getpid();
    cout << "My process ID is: " << pid << endl;

    auto end = chrono::high_resolution_clock::now();
    cout << "Time: " << chrono::duration_cast<chrono::microseconds>(end-start).count() << " us\n";
}
