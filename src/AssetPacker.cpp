//
// Created by sonit on 27-02-2026.
//

#include "AssetPacker.h"
#include <filesystem>
#include <iostream>

#include "AssetEntry.h"

namespace TUtils
{
    AssetPacker::AssetPacker(std::string path)
    {
        std::vector<AssetEntry> entries;
        uintmax_t offset = 0;
        for (auto& dir_entry : std::filesystem::directory_iterator(path)) {
            uintmax_t size = std::filesystem::file_size(dir_entry);
            AssetEntry entry(dir_entry.path().string(),size,offset);
            entries.push_back(entry);
            offset+=size+1;
        }
        for (auto& entry:entries) {
            std::cout<<" path:"<<entry.path<<" size:"<<entry.size<<" offset:"<<entry.offset<<std::endl;

        }
    }
} // TUtils