#include <iostream>
#include <sys/stat.h>
#include <fcntl.h>
using namespace std;

int main() {
    mode_t oldMask = umask(0022);

    cout << "Old mask: " << oldMask << endl;

    int fd = creat("newfile.txt", 0666);

    if(fd < 0)
        cout << "Error creating file\n";
    else
        cout << "File created with umask applied\n";

    return 0;
}
