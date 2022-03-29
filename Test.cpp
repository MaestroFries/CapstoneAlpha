#include <iostream>
#include <sstream>
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
    unsigned char* data = stbi_load(filename.c_str(), &x, &y, &n, 3);
    if (data != nullptr)
    {
        image = std::vector<unsigned char>(data, data + x * y * 3);
    }
    stbi_image_free(data);
    return (data != nullptr);
}

std::string rgb2hex(int r, int g, int b, bool with_head)
{
    std::stringstream ss;
    if (with_head)
        ss << "#";
    ss << std::hex << (r << 16 | g << 8 | b);
    return ss.str();
}

int main()
{
    std::string filename = "C:/Users/781932/Desktop/creeper.jpg";

    int width, height;
    int r,g,b;

    std::vector<unsigned char> image;
    bool success = load_image(image, filename, width, height);
    if (!success)
    {
        std::cout << "Error loading image\n";
        return 1;
    }

    std::cout << "Image width = " << width << '\n';
    std::cout << "Image height = " << height << '\n';

    const size_t RGB = 3;



    
    
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            size_t index = RGB * (y * width + x);
            std::cout << "RGB pixel @ (x = " << x << ", y = " << y << "):"
                << static_cast<int>(image[index + 0]) << " "
                << static_cast<int>(image[index + 1]) << " "
                << static_cast<int>(image[index + 2]) << "\n"
                << "---------------------\n";
            r = static_cast<int>(image[index + 0]);
            g = static_cast<int>(image[index + 1]);
            b = static_cast<int>(image[index + 2]);
            std::cout << " Hex: " << rgb2hex(r, g, b, true) << std::endl;
        }

        if (x == width)
        {
            return 0;
        }
    }


    return 0;
}
