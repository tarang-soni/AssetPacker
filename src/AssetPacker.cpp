//
// Created by sonit on 27-02-2026.
//

#include "AssetPacker.h"
#include <filesystem>
#include <fstream>
#include <iostream>

#include "AssetEntry.h"
#include <algorithm>
namespace TUtils
{
    AssetPacker::AssetPacker(int argc, char **argv)
    {
        //AssetPacker.exe --i "assets/" --o "/asset.dat" --v 0.0.1
        std::string in_path;
        std::string out_path;
        char* version;
        for (int i=1;i<argc;i++)
        {
            std::string arg = argv[i];
            if (arg == "--i" && i+1 < argc)
            {
                in_path = argv[++i];
            }
            else if (arg == "--o" && i+1 < argc)
            {
                out_path = argv[++i];
            }
            else if (arg == "--v" && i+1 < argc)
            {
                std::string s =argv[++i];
                std::erase(s,'.');
                for (int i=0;i<3;i++)
                {
                    version[i] = s[i];
                }
            }
        }
        if (argc>1)
        {
            pack(in_path, out_path, version);
        }
    }
    void AssetPacker::pack(const std::string& in_path,const std::string& out_path,const char version[3]) const
    {
        int count = 0;
        uintmax_t header_size = sizeof(PACKER_ID) + sizeof(version) + sizeof(count);
        uintmax_t offset = 0;

        std::vector<AssetEntry> entries;
        for (auto &dir_entry: std::filesystem::directory_iterator(in_path)) {
            if (std::filesystem::is_regular_file(dir_entry)) count++;
        }
        offset += header_size + (count * sizeof(AssetEntry));
        for (auto &dir_entry: std::filesystem::directory_iterator(in_path)) {
            uintmax_t size = std::filesystem::file_size(dir_entry);
            AssetEntry entry((dir_entry.path().string().c_str()), size, offset);
            entries.push_back(entry);
            offset += size;
        }
        std::ofstream file("pack.dat", std::ios::binary);
        if (file.is_open()) {
            file.write(PACKER_ID, sizeof(PACKER_ID));
            file.write(reinterpret_cast<const char *>(&version), sizeof(version));
            file.write(reinterpret_cast<const char *>(&count), sizeof(count));
            for (auto &entry: entries) {
                file.write(reinterpret_cast<const char *>(entry.path), sizeof(entry.path));
                file.write(reinterpret_cast<const char *>(&entry.size), sizeof(entry.size));
                file.write(reinterpret_cast<const char *>(&entry.offset), sizeof(entry.offset));

                for (auto &asset_entry: entries) {
                    std::cout << " path:" << asset_entry.path << " size:" << asset_entry.size << " offset:" <<
                            asset_entry.offset << std::endl;
                }
                std::ofstream basic_ofstream(out_path, std::ios::binary);
                if (basic_ofstream.is_open()) {
                    basic_ofstream.write(PACKER_ID, sizeof(PACKER_ID));
                    basic_ofstream.write(reinterpret_cast<const char *>(&version), sizeof(version));
                    basic_ofstream.write(reinterpret_cast<const char *>(&count), sizeof(count));
                    for (auto &asset_entry: entries) {
                        basic_ofstream.write(reinterpret_cast<const char *>(asset_entry.path),
                                             sizeof(asset_entry.path));
                        basic_ofstream.write(reinterpret_cast<const char *>(&asset_entry.size),
                                             sizeof(asset_entry.size));
                        basic_ofstream.write(reinterpret_cast<const char *>(&asset_entry.offset),
                                             sizeof(asset_entry.offset));
                    }
                    for (auto &asset_entry: entries) {
                        std::ifstream filestream(asset_entry.path, std::ios::binary | std::ios::ate);
                        if (!filestream.is_open()) {
                            std::cerr << "CRITICAL ERROR: Failed to open " << asset_entry.path << std::endl;
                            return;
                        }
                        auto size = filestream.tellg();
                        filestream.seekg(0, std::ios::beg);
                        std::vector<char> buffer(size);
                        filestream.read(buffer.data(), size);
                        basic_ofstream.write(buffer.data(), size);
                    }
                }
            }
        }
    }
} // TUtils
