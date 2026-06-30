#include <iostream>
#include <windows.h>
#include <chrono>
using namespace std;

int main()
{
    auto start = chrono::high_resolution_clock::now();

    SYSTEM_INFO info;
    GetSystemInfo(&info);

    cout << "Number of processors: " << info.dwNumberOfProcessors << endl;
    cout << "Page size: " << info.dwPageSize << " bytes" << endl;
    cout << "Processor type: " << info.dwProcessorType << endl;

    auto end = chrono::high_resolution_clock::now();
    cout << "Time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " us\n";
}