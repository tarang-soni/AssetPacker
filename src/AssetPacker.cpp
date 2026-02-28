//
// Created by sonit on 27-02-2026.
//

#include "AssetPacker.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include "AssetEntry.h"
#include <algorithm>
#include <vector>
namespace TUtils
{
    AssetPacker::AssetPacker(const int argc, char **argv)
    {
        //AssetPacker.exe --i "assets/" --o "/asset.dat" --v 0.0.1
        std::string in_path;
        std::string out_path;
        char* version = nullptr;
        for (int i=1;i<argc;i++)
        {
            std::string arg = argv[i];
            if (arg == "--i" && i+1 < argc)
            {
                in_path = argv[++i];
                filePath = in_path;
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
    void AssetPacker::pack(const std::string& in_path,const std::string& out_path,const char* version) const
    {
        int count = 0;

        uintmax_t header_size = sizeof(PACKER_ID) + sizeof(version) + sizeof(count);
        uintmax_t offset = 0;
        std::vector<AssetEntry> entries;
        for (auto &dir_entry: std::filesystem::directory_iterator(in_path)) {
            if (std::filesystem::is_regular_file(dir_entry)) count++;
        }
        std::cout<<"Count:"<<count<<std::endl;
        offset += header_size + (count * sizeof(AssetEntry));
        for (auto &dir_entry: std::filesystem::directory_iterator(in_path)) {
            uintmax_t size = std::filesystem::file_size(dir_entry);
            AssetEntry entry((dir_entry.path().generic_string().c_str()), size, offset);
            entries.push_back(entry);
            offset += size;
        }
        std::ofstream file(out_path, std::ios::binary);
        if (file.is_open()) {
            file.write(PACKER_ID, sizeof(PACKER_ID));
            file.write(reinterpret_cast<const char *>(&version), sizeof(version));
            file.write(reinterpret_cast<const char *>(&count), sizeof(count));
            for (auto &entry: entries)
            {
                file.write(reinterpret_cast<const char *>(&entry), sizeof(entry));
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
                file.write(buffer.data(), size);
                filestream.close();
            }
        }
        file.close();
    }

    void AssetPacker::init(const char *path)
    {
        filePath = path;
        std::ifstream file(path, std::ios::binary);
        if (file.is_open())
        {
            file.seekg(0, std::ios::beg);
            char s[4] ;
            file.read(s, sizeof(PACKER_ID));
            if (std::strncmp(s, PACKER_ID,sizeof(PACKER_ID)) != 0)
            {
                std::cerr<<"INVALID PACKER ID: "<<s<<std::endl;
                return;
            }
            //step 1 go to first table of content offset by skipping the name version and save the count
            int count = 0;
            int headerOffset = sizeof(PACKER_ID)+sizeof(const char*);
            file.seekg(headerOffset, std::ios::beg); //size of version
            file.read(reinterpret_cast<char *>(&count),sizeof(count));
            std::cout << "count:" << count << std::endl;
            assetPackMap.clear();
            for (int i =0;i<count;i++)
            {
                AssetEntry entry("",0,0);
                file.read(reinterpret_cast<char *>(&entry), sizeof(AssetEntry));
                PathData dat(entry.offset,entry.size,entry.type);
                assetPackMap.emplace(entry.path,dat);
            }
            std::cout<<"assetPackMap size:"<<assetPackMap.size()<<std::endl;
            file.close();
        }
    }

    std::vector<unsigned char> AssetPacker::getData(const char *path)//todo: save file path in a variable
    {
        std::ifstream file(filePath, std::ios::binary);
        if (file.is_open())
        {
            PathData dat = assetPackMap.at(path);
            std::vector<unsigned char> buffer(dat.size);
            file.seekg(dat.offset, std::ios::beg);
            file.read(reinterpret_cast<char*>(buffer.data()),dat.size);
            return buffer;
        }else
        {
            std::cerr << "CRITICAL ERROR: Failed to open " << path << std::endl;
        }
    }
} // TUtils
