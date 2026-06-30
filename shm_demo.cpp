#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <cstring>
#include <chrono>
using namespace std;
int main() {
    auto start = chrono::high_resolution_clock::now();

    // Create shared memory
    int shmid = shmget(IPC_PRIVATE, 100, IPC_CREAT | 0666);
    if(shmid < 0) { cout << "shmget failed\n"; return 1; }

    // Attach to shared memory
    char* mem = (char*) shmat(shmid, NULL, 0);
    if(mem == (char*)-1) { cout << "shmat failed\n"; return 1; }

    // Write and read
    strcpy(mem, "Hello from shared memory!");
    cout << "Shared memory says: " << mem << endl;

    // Detach
    shmdt(mem);

    auto end = chrono::high_resolution_clock::now();
    cout << "Time: " << chrono::duration_cast<chrono::microseconds>(end-start).count() << " us\n";
}
