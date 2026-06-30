#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sstream>
#include <cmath>
#include <sys/wait.h>
using namespace std;

int main() {
    // ===== Read file =====
    int fd = open("input.txt", O_RDONLY);
    if(fd < 0) {
        cout << "Error opening file\n";
        return 1;
    }

    char buffer[100];
    read(fd, buffer, sizeof(buffer));
    close(fd);

    string data(buffer);
    stringstream ss(data);

    double x[10];
    int N = 0;

    while(ss >> x[N]) {
        N++;
    }

    // ===== Fork process =====
    pid_t pid = fork();

    if(pid < 0) {
        cout << "Fork failed\n";
        return 1;
    }

    // ===== Child: first half =====
    if(pid == 0) {
        cout << "Child computing first half:\n";

        for(int k = 0; k < N/2; k++) {
            double sum = 0;

            for(int n = 0; n < N; n++) {
                sum += x[n] * cos(2 * M_PI * k * n / N);
            }

            cout << sum << endl;
        }
    }
    // ===== Parent: second half =====
    else {
        wait(NULL);

        cout << "Parent computing second half:\n";

        for(int k = N/2; k < N; k++) {
            double sum = 0;

            for(int n = 0; n < N; n++) {
                sum += x[n] * cos(2 * M_PI * k * n / N);
            }

            cout << sum << endl;
        }
    }

    return 0;
}
