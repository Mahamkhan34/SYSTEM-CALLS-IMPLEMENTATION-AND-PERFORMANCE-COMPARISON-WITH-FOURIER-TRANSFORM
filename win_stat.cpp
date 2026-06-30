#include <iostream>
#include <windows.h>
#include <chrono>
using namespace std;

int main()
{
    auto start = chrono::high_resolution_clock::now();

    DWORD attr = GetFileAttributes("input.txt");
    if (attr == INVALID_FILE_ATTRIBUTES)
    {
        cout << "File not found\n";
        return 1;
    }

    cout << "File attributes value: " << attr << endl;
    if (attr & FILE_ATTRIBUTE_READONLY)
        cout << "File is read-only\n";
    else
        cout << "File is writable\n";

    auto end = chrono::high_resolution_clock::now();
    cout << "Time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " us\n";
}