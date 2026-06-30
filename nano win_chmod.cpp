#include <iostream>
#include <windows.h>
#include <chrono>
using namespace std;

int main()
{
    auto start = chrono::high_resolution_clock::now();

    BOOL res = SetFileAttributes("input.txt", FILE_ATTRIBUTE_READONLY);

    if (res)
        cout << "Attribute changed\n";
    else
        cout << "Error\n";

    auto end = chrono::high_resolution_clock::now();
    cout << "Time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " us\n";
}