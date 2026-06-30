#include <iostream>
#include <windows.h>
#include <chrono>
#include <cstring>
using namespace std;

int main()
{
    auto start = chrono::high_resolution_clock::now();

    // Create a file mapping in memory (no actual file)
    HANDLE hMap = CreateFileMapping(INVALID_HANDLE_VALUE, NULL,
                                    PAGE_READWRITE, 0, 1024, "MySharedMem");
    if (hMap == NULL)
    {
        cout << "CreateFileMapping failed\n";
        return 1;
    }

    // Map into address space
    char *mem = (char *)MapViewOfFile(hMap, FILE_MAP_ALL_ACCESS, 0, 0, 1024);
    if (mem == NULL)
    {
        cout << "MapViewOfFile failed\n";
        return 1;
    }

    strcpy(mem, "Hello from mapped memory!");
    cout << "Mapped memory: " << mem << endl;

    UnmapViewOfFile(mem);
    CloseHandle(hMap);

    auto end = chrono::high_resolution_clock::now();
    cout << "Time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " us\n";
    return 0;
}