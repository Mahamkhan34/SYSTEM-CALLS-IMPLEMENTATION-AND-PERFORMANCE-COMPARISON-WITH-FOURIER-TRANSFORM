#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <chrono>
using namespace std;

int main() {
    auto start = chrono::high_resolution_clock::now();

    pid_t pid = fork();

    if(pid < 0) {
        cout << "Fork failed\n";
        return 1;
    }
    else if(pid == 0) {
        // Child process
        cout << "I am Child Process. PID: " << getpid() << endl;
    }
    else {
        // Parent process
        cout << "I am Parent Process. PID: " << getpid() << endl;
        wait(NULL); // wait for child
    }

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);

    cout << "Time taken: " << duration.count() << " microseconds" << endl;

    return 0;
}
