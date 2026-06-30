#include <chrono>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

auto start = chrono::high_resolution_clock::now();int main() {
    int fd[2];   // fd[0] = read, fd[1] = write

    if(pipe(fd) == -1) {
        cout << "Pipe failed\n";
        return 1;
    }

    pid_t pid = fork();

    if(pid < 0) {
        cout << "Fork failed\n";
        return 1;
    }

    if(pid == 0) {
        // Child process
        close(fd[1]); // close write end

        char buffer[100];
        read(fd[0], buffer, sizeof(buffer));

        cout << "Child received: " << buffer << endl;

        close(fd[0]);
    }
    else {
        // Parent process
        close(fd[0]); // close read end

        char message[] = "Hello from Parent";

        write(fd[1], message, sizeof(message));

        close(fd[1]);
        wait(NULL);
    }
if(pid > 0) {   // only parent
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);

    cout << "Time: " << duration.count() << " us" << endl;
}
    return 0;
}
