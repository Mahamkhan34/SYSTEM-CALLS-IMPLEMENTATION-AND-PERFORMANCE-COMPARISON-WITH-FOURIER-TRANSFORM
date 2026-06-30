#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <chrono>
using namespace std;
int main() {
    auto start = chrono::high_resolution_clock::now();

    pid_t pid = fork();
    if(pid == 0) {
        // Child runs the "ls" command using execvp
        char* args[] = {(char*)"ls", NULL};
        execvp("ls", args);
        cout << "execvp failed\n";
    } else {
        wait(NULL);
        auto end = chrono::high_resolution_clock::now();
        cout << "Time: " << chrono::duration_cast<chrono::microseconds>(end-start).count() << " us\n";
    }
}
