//
// Created by kayukin on 01.11.15.
//

#include "MyUNIXLib.h"

string ReadLink(string path) {
    char LinkPath[1024];
    int n = (int) readlink(path.c_str(), LinkPath, 1024);
    if (n == -1) {
        cerr << "error: readlink" << endl;
        cin.get();
        exit(1);
    }
    if (LinkPath[n - 1] == '/')
        LinkPath[n - 1] = 0;
    else
        LinkPath[n] = 0;
    return string(LinkPath);
}

struct stat lstat(string filePath) {
    struct stat result;
    lstat(filePath.c_str(), &result);
    return result;
}

bool operator==(struct stat FirstStat, struct stat SecondStat) {
    return FirstStat.st_dev == SecondStat.st_dev &&
           FirstStat.st_ino == SecondStat.st_ino;
}