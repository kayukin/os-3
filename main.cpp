#include "MyUNIXLib.h"

using namespace std;

string GetCurrentPath() {
    stat RootStat = lstat("/");
    string ResultPath = "";
    string CurrentPath = ".";
    stat CurrentStat = lstat(CurrentPath);
    while (RootStat != CurrentStat) {
        CurrentStat = lstat(CurrentPath);
        string UpDirectory = CurrentPath + "/..";
        Directory directory(UpDirectory);
        list<string> dirs = directory.GetDirectoryNames();
        for (list<string>::iterator i = dirs.begin(); i != dirs.end(); i++) {
            if (*i == ".")
                continue;
            if (*i == "..")
                continue;
            string DirentPath = UpDirectory + "/" + *i;
            if (lstat(DirentPath) == CurrentStat) {
                ResultPath = (string) "/" + *i + ResultPath;
                break;
            }
        }
        CurrentPath += "/..";
    }
    return ResultPath;
}

int CountSymlinks(string OriginalPath) {
    int Result = 0;
    string CurrentPath = OriginalPath;
    while (lstat(CurrentPath) != lstat("/")) {
        Directory directory(CurrentPath);
        list<string> dirs = directory.GetDirectoryNames();
        for (list<string>::iterator i = dirs.begin(); i != dirs.end(); i++) {
            if (*i == ".")
                continue;
            if (*i == "..")
                continue;
            string DirentPath = CurrentPath + "/" + *i;
            try {
                if (IsLink(DirentPath) && (OriginalPath == ReadLink(DirentPath))) {
                    Result++;
                }
            }
            catch (ReadlinkException ex) { cerr << ex.GetMessage(); }
        }
        CurrentPath += "/..";
    }
    return Result;
}

int main(int argc, char *argv[]) {
    string Path = GetCurrentPath();
    cout << "Path: " << Path << endl;
    cout << "Number of symlink's: " << CountSymlinks(Path) << endl;
    return 0;
}