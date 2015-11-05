#include <iostream>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <list>

#ifndef OS_3_MYUNIXLIB_H
#define OS_3_MYUNIXLIB_H

using namespace std;

class ReadlinkException {
private:
    string message;
public:
    ReadlinkException(string msg);

    string GetMessage();
};

#define stat struct stat

stat lstat(string);

string ReadLink(string path);

bool operator==(stat FirstStat, stat SecondStat);
bool operator!=(stat FirstStat, stat SecondStat);

bool IsLink(string);

class Directory {
    DIR* dir;
public:
    Directory(string);
    list<string> GetDirectoryNames()const;
};

#endif //OS_3_MYUNIXLIB_H
