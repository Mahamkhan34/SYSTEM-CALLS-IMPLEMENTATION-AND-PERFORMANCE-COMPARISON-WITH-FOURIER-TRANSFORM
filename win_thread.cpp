#include <iostream>
#include <windows.h>
#include <chrono>
using namespace std;

DWORD WINAPI threadFunc(LPVOID param)
{
    cout << "Child thread running! ID: " << GetCurrentThreadId() << endl;
    return 0;
}

int main()
{
    auto start = chrono::high_resolution_clock::now();

    HANDLE hThread = CreateThread(NULL, 0, threadFunc, NULL, 0, NULL);
    if (hThread == NULL)
    {
        cout << "CreateThread failed\n";
        return 1;
    }

    WaitForSingleObject(hThread, INFINITE);
    CloseHandle(hThread);

    auto end = chrono::high_resolution_clock::now();
    cout << "Time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " us\n";
}