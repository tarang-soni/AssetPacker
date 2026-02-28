//
// Created by sonit on 27-02-2026.
//

#ifndef ASSETPACKER_ASSETENTRY_H
#define ASSETPACKER_ASSETENTRY_H
#include <cstring>
#include <string>
#include <utility>
#include <vector>
#include <algorithm>
#include <cctype>
namespace TUtils
{
    enum class AssetType
    {
        PNG,
        JPEG,
        JPG
    };
    struct AssetEntry
    {
    public:
        char path[128];
        uintmax_t size;
        uintmax_t offset{};
        AssetType type;
        AssetEntry(const char *_path, const uintmax_t size, const uintmax_t offset) : size(size), offset(offset)
        {
            std::strncpy(path, _path, 127);
            std::string pathStr(path);
            type = AssetType::PNG;

            size_t dotPos = pathStr.find_last_of('.');
            if (dotPos != std::string::npos)
            {
                std::string ext = pathStr.substr(dotPos + 1);
                std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
                if (ext == "png")
                {
                    type = AssetType::PNG;
                }
                else if (ext == "jpg")
                {
                    type = AssetType::JPEG;
                }
                else if (ext == "jpeg")
                {
                    type = AssetType::JPEG;
                }
            }
            path[127] = '\0';
        }
    };
}
#endif //ASSETPACKER_ASSETENTRY_H
