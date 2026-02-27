//
// Created by sonit on 27-02-2026.
//

#ifndef ASSETPACKER_ASSETENTRY_H
#define ASSETPACKER_ASSETENTRY_H
#include <string>
#include <utility>
#include <vector>

namespace TUtils
{
    struct AssetEntry {
        public:
            std::string path;
            uintmax_t size;
            std::vector<char> buffer;
            uintmax_t offset{};
        AssetEntry(std::string path, const uintmax_t size,const uintmax_t offset):path(std::move(path)),size(size),offset(offset) {}
    };
}
#endif //ASSETPACKER_ASSETENTRY_H