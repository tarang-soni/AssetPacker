//
// Created by sonit on 27-02-2026.
//

#include "AssetPacker.h"
#include <filesystem>
#include <fstream>
#include <iostream>

#include "AssetEntry.h"

namespace TUtils
{
    AssetPacker::AssetPacker(std::string path,int version):_ver(version)
    {
        int count = 0;
        uintmax_t header_size = 4 + sizeof(version)+sizeof(count);
        uintmax_t offset = 0;




        std::vector<AssetEntry> entries;
        for (auto& dir_entry : std::filesystem::directory_iterator(path)) {
            if (std::filesystem::is_regular_file(dir_entry)) count++;
        }
        offset+=header_size +(count*sizeof(AssetEntry));
        for (auto& dir_entry : std::filesystem::directory_iterator(path)) {
            uintmax_t size = std::filesystem::file_size(dir_entry);
            AssetEntry entry((dir_entry.path().string().c_str()),size,offset);
            entries.push_back(entry);
            offset+=size;
        }
        for (auto& entry:entries)
        {
            std::cout<<" path:"<<entry.path<<" size:"<<entry.size<<" offset:"<<entry.offset<<std::endl;
        }
        std::ofstream file("pack.dat",std::ios::binary);
        if (file.is_open()) {
            file.write(getPackerID(),sizeof(getPackerID()));
            file.write(reinterpret_cast<const char*>(&version),sizeof(version));
            file.write(reinterpret_cast<const char*>(&count),sizeof(count));
            for (auto& entry:entries) {
                file.write(reinterpret_cast<const char *>(entry.path),sizeof(entry.path));
                file.write(reinterpret_cast<const char *>(&entry.size),sizeof(entry.size));
                file.write(reinterpret_cast<const char *>(&entry.offset),sizeof(entry.offset));
            }
            for (auto& entry:entries) {
                std::ifstream filestream(entry.path,std::ios::binary | std::ios::ate);
                if (!filestream.is_open()) {
                    std::cerr << "CRITICAL ERROR: Failed to open " << entry.path << std::endl;
                    return;
                }
                auto size = filestream.tellg();
                filestream.seekg(0,std::ios::beg);
                std::vector<char> buffer(size);
                filestream.read(buffer.data(),size);
                file.write(buffer.data(),size);
            }
        }

    }

    const char* AssetPacker::getPackerID() {
        return PACKER_ID;
    }
} // TUtils