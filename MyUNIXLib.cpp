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

bool IsLink(string string1) {
    return S_ISLNK(lstat(string1).st_mode);
}

Directory::Directory(string string1) {
    dir = opendir(string1.c_str());
}

list<string> Directory::GetDirectoryNames() const {
    dirent *dirent;
    list<string> res;
    while ((dirent = readdir(dir)) != NULL)
        res.push_back(dirent->d_name);
    return res;
}

bool operator!=(stat FirstStat, stat SecondStat) {
    return !(FirstStat == SecondStat);
}
