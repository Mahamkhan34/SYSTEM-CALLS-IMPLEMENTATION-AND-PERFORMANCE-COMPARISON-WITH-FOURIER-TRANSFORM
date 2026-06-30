#include <iostream>
#include <sys/stat.h>
#include <chrono>
using namespace std;
int main() {
    auto start = chrono::high_resolution_clock::now();

    int result = chmod("input.txt", 0644);
    if(result == 0) cout << "Permissions changed successfully\n";
    else cout << "Error\n";

    auto end = chrono::high_resolution_clock::now();
    cout << "Time: " << chrono::duration_cast<chrono::microseconds>(end-start).count() << " us\n";
}
