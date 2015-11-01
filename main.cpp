#include "MyUNIXLib.h"

using namespace std;

string GetCurrentPath() {
    struct stat RootStat = lstat("/");
    string ResultPath = "";
    string CurrentPath = ".";
    while (true) {
        struct stat CurrentStat = lstat(CurrentPath);
        if (RootStat == CurrentStat) {
            return ResultPath;
        }
        string UpDirectory = CurrentPath + "/..";
        DIR *Directory = opendir(UpDirectory.c_str());
        dirent *Dirent;
        while ((Dirent = readdir(Directory)) != NULL) {
            if (!strcmp(Dirent->d_name, "."))
                continue;
            if (!strcmp(Dirent->d_name, ".."))
                continue;
            string DirentPath = UpDirectory + "/" + Dirent->d_name;
            if (lstat(DirentPath) == CurrentStat) {
                ResultPath = (string) "/" + Dirent->d_name + ResultPath;
                break;
            }
        }
        CurrentPath += "/..";
    }
}

int CountSymlinks(string OriginalPath) {
    int Result = 0;
    string CurrentPath = OriginalPath;
    while (true) {
        DIR *Directory = opendir(CurrentPath.c_str());
        dirent *Dirent;
        while ((Dirent = readdir(Directory)) != NULL) {
            if (!strcmp(Dirent->d_name, "."))
                continue;
            if (!strcmp(Dirent->d_name, ".."))
                continue;
            string DirentPath = CurrentPath + "/" + Dirent->d_name;
            if (S_ISLNK(lstat(DirentPath).st_mode) && (OriginalPath == ReadLink(DirentPath))) {
                Result++;
            }
        }
        if (lstat(CurrentPath) == lstat("/")) {
            return Result;
        }
        CurrentPath += "/..";
    }
}

int main() {
    string Path = GetCurrentPath();
    cout << "Path: " << Path << endl;
    cout << "Number of symlink's: " << CountSymlinks(Path) << endl;
    return 0;
}