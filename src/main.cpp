
#include <cstdint>
#include  <iostream>
#include <vector>
#include <fstream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include "AssetPacker.h"
using namespace std;

int main(int argc, char **argv)
{
    TUtils::AssetPacker packer;
    packer.init("pack.dat");
    //packer.pack("./assets","pack.dat","0.0.1");


    std::vector<unsigned char> buffer = packer.getData("./assets/test.png");

    int width, height, channels;
    unsigned char *imageData = stbi_load_from_memory(buffer.data(), buffer.size(), &width, &height, &channels, 0);
    if (imageData != nullptr)
    {
        int stride = width * channels;
        int success = stbi_write_png(
            "extracted_test.png", // The output file name
            width, // From stbi_load
            height, // From stbi_load
            channels, // From stbi_load
            imageData, // The decoded raw pixel data
            stride // The math we just did
        );
        if (success)
        {
            std::cout << "Successfully extracted and saved the PNG!" << std::endl;
        }

        // 4. Always free the STB memory when you are done!
        stbi_image_free(imageData);
    } else
    {
        std::cerr << "STB failed to decode the image data." << std::endl;
    }
    return 0;
}
