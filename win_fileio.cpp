#include <iostream>
#include <windows.h>
#include <chrono>
using namespace std;

int main()
{
    auto start = chrono::high_resolution_clock::now();

    // Create input file first
    HANDLE hWrite = CreateFile("input.txt", GENERIC_WRITE, 0, NULL,
                               CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    const char *data = "1 2 3 4 5";
    DWORD written;
    WriteFile(hWrite, data, strlen(data), &written, NULL);
    CloseHandle(hWrite);

    // Now read it back
    HANDLE hRead = CreateFile("input.txt", GENERIC_READ, 0, NULL,
                              OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hRead == INVALID_HANDLE_VALUE)
    {
        cout << "Error opening file\n";
        return 1;
    }

    char buffer[100] = {0};
    DWORD bytesRead;
    ReadFile(hRead, buffer, sizeof(buffer), &bytesRead, NULL);
    CloseHandle(hRead);

    cout << "Data read: " << buffer << endl;

    auto end = chrono::high_resolution_clock::now();
    cout << "Time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " us\n";
    return 0;
}