#include <iostream>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>

#ifndef OS_3_MYUNIXLIB_H
#define OS_3_MYUNIXLIB_H

using namespace std;

struct stat lstat(string);

string ReadLink(string path);

bool operator==(struct stat FirstStat, struct stat SecondStat);

#endif //OS_3_MYUNIXLIB_H
