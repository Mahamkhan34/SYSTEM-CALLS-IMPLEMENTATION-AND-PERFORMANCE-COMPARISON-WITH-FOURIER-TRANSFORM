#include <iostream>
#include <windows.h>
#include <chrono>
using namespace std;

int main()
{
    auto start = chrono::high_resolution_clock::now();

    STARTUPINFO si = {sizeof(si)};
    PROCESS_INFORMATION pi;

    // Run "cmd /c dir" as a child process
    char cmd[] = "cmd /c dir";

    if (!CreateProcess(NULL, cmd, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
    {
        cout << "CreateProcess failed\n";
        return 1;
    }

    WaitForSingleObject(pi.hProcess, INFINITE);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    auto end = chrono::high_resolution_clock::now();
    cout << "Time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " us\n";
    return 0;
}