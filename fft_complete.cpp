#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sstream>
#include <cmath>
#include <chrono>
using namespace std;

int main() {
    auto start = chrono::high_resolution_clock::now();

    // STEP 1: Read signal from file
    int fd = open("input.txt", O_RDONLY);
    if(fd < 0) { cout << "Error opening file\n"; return 1; }

    char buffer[200];
    read(fd, buffer, sizeof(buffer));
    close(fd);

    // Parse numbers
    string data(buffer);
    stringstream ss(data);
    double x[20];
    int N = 0;
    while(ss >> x[N]) N++;

    // STEP 2: Create pipe
    int pipefd[2];
    if(pipe(pipefd) == -1) { cout << "Pipe failed\n"; return 1; }

    // STEP 3: Fork
    pid_t pid = fork();
    if(pid < 0) { cout << "Fork failed\n"; return 1; }

    // STEP 4: Child computes first half, sends via pipe
    if(pid == 0) {
        close(pipefd[0]); // child doesn't read

        double child_result[10];
        for(int k = 0; k < N/2; k++) {
            child_result[k] = 0;
            for(int n = 0; n < N; n++) {
                child_result[k] += x[n] * cos(2 * M_PI * k * n / N);
            }
        }

        // Send to parent via pipe
        write(pipefd[1], child_result, sizeof(double) * (N/2));
        close(pipefd[1]);

    } else {
        // STEP 5: Parent computes second half
        close(pipefd[1]); // parent doesn't write

        // Compute second half
        double parent_result[10];
        for(int k = N/2; k < N; k++) {
            parent_result[k - N/2] = 0;
            for(int n = 0; n < N; n++) {
                parent_result[k - N/2] += x[n] * cos(2 * M_PI * k * n / N);
            }
        }

        // Receive child's half
        double child_result[10];
        read(pipefd[0], child_result, sizeof(double) * (N/2));
        close(pipefd[0]);

        wait(NULL);

        // STEP 6: Combine and print
        cout << "=== FFT Results ===\n";
        for(int k = 0; k < N/2; k++)
            cout << "X[" << k << "] = " << child_result[k] << "  (child)\n";
        for(int k = 0; k < N/2; k++)
            cout << "X[" << k + N/2 << "] = " << parent_result[k] << "  (parent)\n";

        // STEP 7: Write output to file
        int out_fd = open("result.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        for(int k = 0; k < N/2; k++) {
            string line = "X[" + to_string(k) + "] = " + to_string(child_result[k]) + "\n";
            write(out_fd, line.c_str(), line.size());
        }
        for(int k = 0; k < N/2; k++) {
            string line = "X[" + to_string(k + N/2) + "] = " + to_string(parent_result[k]) + "\n";
            write(out_fd, line.c_str(), line.size());
        }
        close(out_fd);

        auto end = chrono::high_resolution_clock::now();
        auto dur = chrono::duration_cast<chrono::microseconds>(end - start);
        cout << "\nTime taken: " << dur.count() << " microseconds\n";
        cout << "Output saved to result.txt\n";
    }

    return 0;
}
