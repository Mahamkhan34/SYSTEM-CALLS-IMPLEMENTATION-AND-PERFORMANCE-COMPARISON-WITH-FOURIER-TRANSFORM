#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

int main()
{
    pid_t pid = fork();

    if (pid == 0)
    {
        cout << "Child running...\n";
        sleep(2);
        cout << "Child finished\n";
    }
    else
    {
        wait(NULL); // parent waits
        cout << "Parent resumes after child\n";
    }
}