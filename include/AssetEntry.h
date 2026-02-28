//
// Created by sonit on 27-02-2026.
//

#ifndef ASSETPACKER_ASSETENTRY_H
#define ASSETPACKER_ASSETENTRY_H
#include <cstring>
#include <string>
#include <utility>
#include <vector>

namespace TUtils
{
    struct AssetEntry
    {
    public:
        char path[128];
        uintmax_t size;
        uintmax_t offset{};

        AssetEntry(const char *_path, const uintmax_t size, const uintmax_t offset) : size(size), offset(offset)
        {
            std::strncpy(path, _path, 127);
            path[127] = '\0';
        }
    };
}
#endif //ASSETPACKER_ASSETENTRY_H
