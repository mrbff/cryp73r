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
        //std::cout << targetPath + " is a file" << std::endl;
        fun(targetPath);
    else if (is_directory(targetPath)) {
        struct dirent* entry;
        DIR* dir = opendir(targetPath.c_str());

        if (dir == nullptr) {
            std::cerr << "Could not open " + targetPath + " directory." << std::endl;
            return ;
        }
        
    //    std::cout << targetPath + " directory open" << std::endl;
        while ((entry = readdir(dir)) != nullptr) {
            std::string filename(entry->d_name);
            if (filename != ".." && filename != ".")
            {   
                filename = targetPath + "/" + filename;
                f_iterator(filename);
            }
        }

        closedir(dir);
    }

    ///if target == normal file apply fun and return
    ///else create filesArray and for (i < num files) {f_iterator(filesArray[i])}

    //identify if target is a dir
    //if target is a dir deep dive until there are no more subdirs
    //apply fun to each file
}