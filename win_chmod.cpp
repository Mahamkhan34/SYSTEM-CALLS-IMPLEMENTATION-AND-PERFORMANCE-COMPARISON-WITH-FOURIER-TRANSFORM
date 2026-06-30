#include <iostream>
#include <windows.h>
#include <chrono>
using namespace std;

int main()
{
    auto start = chrono::high_resolution_clock::now();

    BOOL result = SetFileAttributes("input.txt", FILE_ATTRIBUTE_NORMAL);
    if (result)
        cout << "File attributes set successfully\n";
    else
        cout << "Failed\n";

    auto end = chrono::high_resolution_clock::now();
    cout << "Time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " us\n";
}