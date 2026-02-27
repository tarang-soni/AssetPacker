#include <cstdint>
#include  <iostream>

#include "AssetPacker.h"
#include <fstream>
#include <vector>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>
using namespace std;

int main(int argc,char** argv)
{
    TUtils::AssetPacker packer("assets",0);

    ifstream file("pack.dat",ios::binary);
    if (!file.is_open()) {
        cerr<<"Error opening file"<<endl;
        return 1;
    }
    file.seekg(8,ios::beg);
    int fileCnt = 0;
    file.read(reinterpret_cast<char*>(&fileCnt),sizeof(fileCnt));
    cout<<"File Count: "<<fileCnt<<endl;
    uintmax_t fileSize,fileOffset;
    char path[128];
    file.read(reinterpret_cast<char*>(&path),sizeof(path));
    file.read(reinterpret_cast<char*>(&fileSize),sizeof(fileSize));
    file.read(reinterpret_cast<char*>(&fileOffset),sizeof(fileOffset));

    std::vector<unsigned char> buffer(19460);
    file.seekg(fileOffset,ios::beg);
    file.read(reinterpret_cast<char*>(buffer.data()),fileSize);
    int width, height, channels;
    unsigned char* imageData = stbi_load_from_memory(buffer.data(),buffer.size(),&width,&height,&channels,0);
    if (imageData!=nullptr) {
        int stride = width*channels;
        int success = stbi_write_png(
        "extracted_test.png",  // The output file name
        width,                 // From stbi_load
        height,                // From stbi_load
        channels,              // From stbi_load
        imageData,             // The decoded raw pixel data
        stride        // The math we just did
    );
        if (success) {
            std::cout << "Successfully extracted and saved the PNG!" << std::endl;
        }

        // 4. Always free the STB memory when you are done!
        stbi_image_free(imageData);
    }
    else {
        std::cerr << "STB failed to decode the image data." << std::endl;
    }
    return 0;
}