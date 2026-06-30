#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <chrono>
using namespace std;

int main() {
    pid_t pid = fork();

    if(pid == 0) {
        sleep(1);
    } else {
        auto start = chrono::high_resolution_clock::now();

        wait(NULL);

        auto end = chrono::high_resolution_clock::now();

        cout << "Wait completed\n";
        cout << "Time: " << chrono::duration_cast<chrono::microseconds>(end-start).count() << " us\n";
    }

    return 0;
}
