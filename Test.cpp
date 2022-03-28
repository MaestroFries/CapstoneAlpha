#include <iostream>
#include <vector>

extern "C" {
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
}

// Loads as RGBA... even if file is only RGB
// Feel free to adjust this if you so please, by changing the 4 to a 0.
bool load_image(std::vector<unsigned char>& image, const std::string& filename, int& x, int& y)
{
    int n;
    unsigned char* data = stbi_load(filename.c_str(), &x, &y, &n, 4);
    if (data != nullptr)
    {
        image = std::vector<unsigned char>(data, data + x * y * 4);
    }
    stbi_image_free(data);
    return (data != nullptr);
}

int main()
{
    std::string filename = "C:/Users/781932/Desktop/mario.jpg";

    int width, height;
    std::vector<unsigned char> image;
    bool success = load_image(image, filename, width, height);
    if (!success)
    {
        std::cout << "Error loading image\n";
        return 1;
    }

    std::cout << "Image width = " << width << '\n';
    std::cout << "Image height = " << height << '\n';

    const size_t RGBA = 4;

    int x = 50;
    int y = 230;
    size_t index = RGBA * (y * width + x);
    std::cout << "RGBA pixel @ (x=3, y=4): "
        << static_cast<int>(image[index + 0]) << " "
        << static_cast<int>(image[index + 1]) << " "
        << static_cast<int>(image[index + 2]) << " "
        << static_cast<int>(image[index + 3]) << '\n';

    return 0;
}
