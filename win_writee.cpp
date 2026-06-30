#include <iostream>
#include <windows.h>
#include <chrono>
#include <cstring>
using namespace std;

int main()
{
    auto start = chrono::high_resolution_clock::now();

    HANDLE hFile = CreateFile("output.txt", GENERIC_WRITE, 0, NULL,
                              CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    const char *data = "Hello Windows";
    DWORD written;

    WriteFile(hFile, data, strlen(data), &written, NULL);

    auto end = chrono::high_resolution_clock::now();

    cout << "Data written\n";
    cout << "Time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " us\n";

    CloseHandle(hFile);
    return 0;
}