//
// Created by sonit on 27-02-2026.
//

#ifndef ASSETPACKER_ASSETPACKER_H
#define ASSETPACKER_ASSETPACKER_H
#include <string>
//first it will go to the folder, create a string stream, first pak1 then a count will be maintained for num of files with supported file types
//phase 2- create threads for n number of files at a time
//lets say 10 threads, every thread will read the 10 files first, and keep a data pocket ready. like path,size offset and byteval
//suppose everything is done, now its time to write,first thread will take the lock and write the path and the offset count starts from 0,
//so it writes the path, size,offset, and the byteval. now next thread will start writing between byteval and last threads path etc
namespace TUtils {
    class AssetPacker
    {
    public:
        AssetPacker(std::string path);    //AssetPacker.exe --i "assets/" --o "/asset.dat"
        virtual ~AssetPacker() = default;
    private:

    };
} // TUtils

#endif //ASSETPACKER_ASSETPACKER_H