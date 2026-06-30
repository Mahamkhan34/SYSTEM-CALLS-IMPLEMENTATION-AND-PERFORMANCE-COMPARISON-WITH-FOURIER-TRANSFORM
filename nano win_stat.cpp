#include <iostream>
#include <windows.h>
#include <chrono>
using namespace std;

int main()
{
    auto start = chrono::high_resolution_clock::now();

    WIN32_FILE_ATTRIBUTE_DATA info;
    if (GetFileAttributesEx("input.txt", GetFileExInfoStandard, &info))
    {
        cout << "File size: " << info.nFileSizeLow << endl;
    }
    else
    {
        cout << "Error\n";
    }

    auto end = chrono::high_resolution_clock::now();
    cout << "Time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " us\n";
}