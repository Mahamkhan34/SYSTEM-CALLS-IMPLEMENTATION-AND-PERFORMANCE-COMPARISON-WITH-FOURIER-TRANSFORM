#include <iostream>
#include <windows.h>
#include <chrono>
#include <cstring>
using namespace std;

int main()
{
    auto start = chrono::high_resolution_clock::now();

    HANDLE hRead, hWrite;
    SECURITY_ATTRIBUTES sa = {sizeof(sa), NULL, TRUE};

    if (!CreatePipe(&hRead, &hWrite, &sa, 0))
    {
        cout << "CreatePipe failed\n";
        return 1;
    }

    // Write to pipe
    const char *msg = "Hello from pipe!";
    DWORD written;
    WriteFile(hWrite, msg, strlen(msg) + 1, &written, NULL);
    CloseHandle(hWrite);

    // Read from pipe
    char buffer[100] = {0};
    DWORD bytesRead;
    ReadFile(hRead, buffer, sizeof(buffer), &bytesRead, NULL);
    CloseHandle(hRead);

    cout << "Pipe received: " << buffer << endl;

    auto end = chrono::high_resolution_clock::now();
    cout << "Time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " us\n";
    return 0;
}