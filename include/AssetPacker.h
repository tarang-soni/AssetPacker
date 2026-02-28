//
// Created by sonit on 27-02-2026.
//

#ifndef ASSETPACKER_ASSETPACKER_H
#define ASSETPACKER_ASSETPACKER_H
#include <string>
#include <unordered_map>
#include <vector>

//DONE 1: move the packing logic in its own function. it will execute only if i type commmands like pack --i "path" --o "path"
//DONE 2: create a new data value i.e, enum, in assetentry for identifying the type of image, png jpeg etc

/*DONE 3:
    create unpacker logic in which it will detect if its packed using the same class by comparing packer_id
    parse it and store the table of content part in a hashmap which will be easier to find the images or anything stored in it
*/

//DONE 4: create a getData function which will take a path as input and find it in hashmap. it will do its logic that is use size and offset to pinpoint the data and return the buffered vector

namespace TUtils
{
    enum class AssetType;
    struct PathData
    {
        public:
            int offset;
            int size;
            AssetType type;

            PathData(int _offset,int _size,AssetType _type):offset(_offset),size(_size),type(_type){}
    };
    class AssetPacker
    {
    private:
        const char PACKER_ID[4] = {'P', 'A', 'K', '1'};
        std::unordered_map<std::string, PathData> assetPackMap;

    public:
        //AssetPacker.exe --i "assets/" --o "/asset.dat"
        AssetPacker(int argc, char **argv);
        AssetPacker()=default;
        void pack(const std::string& in_path, const std::string& out_path, const char version[3]) const;
        void init(const char* path);

        virtual ~AssetPacker() = default;
    //private:
        std::vector<unsigned char> getData(const char* path);
    };
} // TUtils

#endif //ASSETPACKER_ASSETPACKER_H
