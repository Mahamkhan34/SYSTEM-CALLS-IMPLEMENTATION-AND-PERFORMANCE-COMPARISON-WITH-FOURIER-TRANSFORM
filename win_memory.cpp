#include <iostream>
#include <windows.h>
#include <chrono>
#include <cstring>
using namespace std;

int main()
{
    auto start = chrono::high_resolution_clock::now();

    // Allocate memory
    void *mem = VirtualAlloc(NULL, 1024, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (mem == NULL)
    {
        cout << "VirtualAlloc failed\n";
        return 1;
    }

    // Use it
    strcpy((char *)mem, "Hello from VirtualAlloc!");
    cout << "Memory says: " << (char *)mem << endl;

    // Free it
    VirtualFree(mem, 0, MEM_RELEASE);
    cout << "Memory freed\n";

    auto end = chrono::high_resolution_clock::now();
    cout << "Time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " us\n";
    return 0;
}