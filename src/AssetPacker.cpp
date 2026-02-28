//
// Created by sonit on 27-02-2026.
//

#include "AssetPacker.h"
#include <filesystem>
#include <fstream>
#include <iostream>

#include "AssetEntry.h"
//TODO: move the packing logic in its own function. it will execute only if i type commmands like pack --i "path" --o "path"
//TODO: create a separate file to just store the stride values for all the data types

/*TODO:
    create unpacker logic in which it will detect if its packed using the same class by comparing packer_id
    it parse it and store the table of content part in a hashmap which will be easier to find the images or anything stored in it
*/
//TODO: create a getData function which will take a path as input and find it in hashmap. it will do its logic that is use size and offset to pinpoint the data and return the buffered vector
namespace TUtils
{
    AssetPacker::AssetPacker(std::string path, int version) : _ver(version)
    {
        int count = 0;
        uintmax_t header_size = sizeof(PACKER_ID) + sizeof(version) + sizeof(count);
        uintmax_t offset = 0;

        std::vector<AssetEntry> entries;
        for (auto &dir_entry: std::filesystem::directory_iterator(path))
        {
            if (std::filesystem::is_regular_file(dir_entry)) count++;
        }
        offset += header_size + (count * sizeof(AssetEntry));
        for (auto &dir_entry: std::filesystem::directory_iterator(path))
        {
            uintmax_t size = std::filesystem::file_size(dir_entry);
            AssetEntry entry((dir_entry.path().string().c_str()), size, offset);
            entries.push_back(entry);
            offset += size;
        }
<<<<<<< Updated upstream
        std::ofstream file("pack.dat",std::ios::binary);
        if (file.is_open()) {
            file.write(getPackerID(),sizeof(getPackerID()));
            file.write(reinterpret_cast<const char*>(&version),sizeof(version));
            file.write(reinterpret_cast<const char*>(&count),sizeof(count));
            for (auto& entry:entries) {
                file.write(reinterpret_cast<const char *>(entry.path),sizeof(entry.path));
                file.write(reinterpret_cast<const char *>(&entry.size),sizeof(entry.size));
                file.write(reinterpret_cast<const char *>(&entry.offset),sizeof(entry.offset));
=======
        for (auto &entry: entries)
        {
            std::cout << " path:" << entry.path << " size:" << entry.size << " offset:" << entry.offset << std::endl;
        }
        std::ofstream file("pack.dat", std::ios::binary);
        if (file.is_open())
        {
            file.write(PACKER_ID, sizeof(PACKER_ID));
            file.write(reinterpret_cast<const char *>(&version), sizeof(version));
            file.write(reinterpret_cast<const char *>(&count), sizeof(count));
            for (auto &entry: entries)
            {
                file.write(reinterpret_cast<const char *>(entry.path), sizeof(entry.path));
                file.write(reinterpret_cast<const char *>(&entry.size), sizeof(entry.size));
                file.write(reinterpret_cast<const char *>(&entry.offset), sizeof(entry.offset));
>>>>>>> Stashed changes
            }
            for (auto &entry: entries)
            {
                std::ifstream filestream(entry.path, std::ios::binary | std::ios::ate);
                if (!filestream.is_open())
                {
                    std::cerr << "CRITICAL ERROR: Failed to open " << entry.path << std::endl;
                    return;
                }
                auto size = filestream.tellg();
                filestream.seekg(0, std::ios::beg);
                std::vector<char> buffer(size);
                filestream.read(buffer.data(), size);
                file.write(buffer.data(), size);
            }
        }

    }

    const char* AssetPacker::getPackerID() {
        return PACKER_ID;
    }
} // TUtils
