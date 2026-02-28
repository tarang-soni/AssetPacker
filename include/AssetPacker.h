//
// Created by sonit on 27-02-2026.
//

#ifndef ASSETPACKER_ASSETPACKER_H
#define ASSETPACKER_ASSETPACKER_H
#include <string>

namespace TUtils
{
    class AssetPacker
    {
    private:
        const char PACKER_ID[4] = {'P', 'A', 'K', '1'};
        int _ver;

    public:
        //AssetPacker.exe --i "assets/" --o "/asset.dat"
        AssetPacker(std::string path, int version);

        virtual ~AssetPacker() = default;

        void pack();
<<<<<<< Updated upstream
    private:
        const char* getPackerID();

=======
>>>>>>> Stashed changes
    };
} // TUtils

#endif //ASSETPACKER_ASSETPACKER_H
