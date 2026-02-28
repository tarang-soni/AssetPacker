//
// Created by sonit on 27-02-2026.
//

#ifndef ASSETPACKER_ASSETPACKER_H
#define ASSETPACKER_ASSETPACKER_H
#include <string>
//DONE 1: move the packing logic in its own function. it will execute only if i type commmands like pack --i "path" --o "path"
//TODO 2: create a new data value i.e, enum, in assetentry for identifying the type of image, png jpeg etc
//TODO 3: create a separate file to just store the stride values for all the data types

/*TODO 4:
    create unpacker logic in which it will detect if its packed using the same class by comparing packer_id
    it parse it and store the table of content part in a hashmap which will be easier to find the images or anything stored in it
*/
//TODO 5: create a getData function which will take a path as input and find it in hashmap. it will do its logic that is use size and offset to pinpoint the data and return the buffered vector

namespace TUtils
{
    class AssetPacker
    {
    private:
        const char PACKER_ID[4] = {'P', 'A', 'K', '1'};
        int _ver{};

    public:
        //AssetPacker.exe --i "assets/" --o "/asset.dat"
        AssetPacker(int argc, char **argv);
        AssetPacker()=default;
        void pack(const std::string& in_path, const std::string& out_path, const char version[3]) const;
        virtual ~AssetPacker() = default;
    };
} // TUtils

#endif //ASSETPACKER_ASSETPACKER_H
