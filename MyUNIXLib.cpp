#include "MyUNIXLib.h"

string ReadLink(string path) {
    char LinkPath[1024];
    int n = (int) readlink(path.c_str(), LinkPath, 1024);
    if (n == -1) {
        throw ReadlinkException(path + " is not symlink\n");
    }
    if (LinkPath[n - 1] == '/')
        LinkPath[n - 1] = 0;
    else
        LinkPath[n] = 0;
    return string(LinkPath);
}

stat lstat(string filePath) {
    stat result;
    lstat(filePath.c_str(), &result);
    return result;
}

bool operator==(stat FirstStat, stat SecondStat) {
    return FirstStat.st_dev == SecondStat.st_dev &&
           FirstStat.st_ino == SecondStat.st_ino;
}

ReadlinkException::ReadlinkException(string msg) {
    message = msg;
}

string ReadlinkException::GetMessage() {
    return message;
}