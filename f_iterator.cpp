#include "cryp73r.hpp"

void f_iterator(std::string targetPath)
{
    fun(targetPath);
    ///if target == normal file apply fun and return
    ///else create filesArray and for (i < num files) {f_iterator(filesArray[i])}

    //identify if target is a dir
    //if target is a dir deep dive until there are no more subdirs
    //apply fun to each file
}