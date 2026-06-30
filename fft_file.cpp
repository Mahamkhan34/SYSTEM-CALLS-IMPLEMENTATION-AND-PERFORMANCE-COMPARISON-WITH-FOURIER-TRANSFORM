#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sstream>
#include <cmath>
using namespace std;

int main() {
    // STEP 1: open file
    int fd = open("input.txt", O_RDONLY);
    if(fd < 0) {
        cout << "Error opening file\n";
        return 1;
    }

    // STEP 2: read file
    char buffer[100];
    int bytes = read(fd, buffer, sizeof(buffer));
    close(fd);

    // STEP 3: convert string → numbers
    string data(buffer);
    stringstream ss(data);

    double x[10];
    int N = 0;

    while(ss >> x[N]) {
        N++;
    }

    // STEP 4: FFT
    cout << "FFT Output:\n";

    for(int k = 0; k < N; k++) {
        double sum = 0;

        for(int n = 0; n < N; n++) {
            sum += x[n] * cos(2 * M_PI * k * n / N);
        }

        cout << sum << endl;
    }

    return 0;
}
