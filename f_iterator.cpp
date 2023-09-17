#include "cryp73r.hpp"

bool is_directory(const std::string& path) {
    struct stat buf;
    stat(path.c_str(), &buf);
    return S_ISDIR(buf.st_mode);
}

bool is_file(const std::string& path) {
    struct stat buf;
    stat(path.c_str(), &buf);
    return S_ISREG(buf.st_mode);
}

void f_iterator(std::string targetPath)
{
    if (is_file(targetPath))
        fun(targetPath);
    else if (is_directory(targetPath)) {
        struct dirent* entry;
        DIR* dir = opendir(&targetPath[0]);

        if (dir == nullptr) {
            std::cerr << "Could not open " + targetPath + " directory." << std::endl;
            return ;
        }
        
        while ((entry = readdir(dir)) != nullptr) {
            f_iterator((std::string)entry->d_name);
        }

        closedir(dir);
    }

    ///if target == normal file apply fun and return
    ///else create filesArray and for (i < num files) {f_iterator(filesArray[i])}

    //identify if target is a dir
    //if target is a dir deep dive until there are no more subdirs
    //apply fun to each file
}