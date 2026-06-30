#include <iostream>
#include <windows.h>
#include <chrono>
#include <cstring>
using namespace std;

int main()
{
    auto start = chrono::high_resolution_clock::now();

    HANDLE hFile = CreateFile("result_win.txt", GENERIC_WRITE, 0, NULL,
                              CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        cout << "Error creating file\n";
        return 1;
    }

    const char *content = "FFT Result from Windows\nX[0] = 15\nX[1] = -2.5\n";
    DWORD written;
    WriteFile(hFile, content, strlen(content), &written, NULL);
    CloseHandle(hFile);

    cout << "Written " << written << " bytes to result_win.txt\n";

    auto end = chrono::high_resolution_clock::now();
    cout << "Time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " us\n";
}