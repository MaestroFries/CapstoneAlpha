#include <iostream>
#include <sstream>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>


using namespace cv;
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
    std::string filename = "C:/Users/Francis/Documents/images/mario.jpg";

    int width, height;
    int r, g, b;
    int x, y;
    bool continueSearch = true;
    int response;
    
    
    
    
    

    std::vector<unsigned char> image;
    bool success = load_image(image, filename, width, height);
    if (!success)
    {
        std::cout << "Error loading image\n";
        return 1;
    }
    const size_t RGB = 3;

    std::cout << "Image Location: " << filename << "\n";
    std::cout << "Image width = " << width << '\n';
    std::cout << "Image height = " << height << "\n\n--------------------------------\n";

    
    
    while (continueSearch)
    {
        std::cout << "Select x pixel coordinate:\n";
        std::cin >> x;
        std::cout << "X: " << x << "\nSelect y pixel coordinate:\n";
        std::cin >> y;
        std::cout << "X: " << x << " | Y: " << y << "\n\n\n\n"
            << "--------------------------------";

        size_t index = RGB * (y * width + x);
        r = static_cast<int>(image[index + 0]);
        g = static_cast<int>(image[index + 1]);
        b = static_cast<int>(image[index + 2]);

        

        std::cout << "\nRGB Value: " << r << " " << g << " " << b << "\n";

        
        std::cout << "Hex Value: " << rgb2hex(r, g, b, true)
            << "\n--------------------------------\n";
        //Afternoon goal:get the circle and text to display on an image.
        //
        Mat givenImage = imread(filename);

        circle(givenImage, Point(x, y), 10, Scalar(255,255,255), 2);
        putText(givenImage, rgb2hex(r, g, b, true), Point(x + 30, y), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 2, false);
        imshow("Colour", givenImage);
        waitKey(0);
        destroyWindow("Colour");

        

        
        std::cout << "Continue RGB search? 0 = yes | 1 = no\n\n";
        std::cin >> response;

        if (response == 1)
        {
            continueSearch = false;
        }
           

    }



    return 0;
     






    /*  Code for looping through the each pixel's RGB data.
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
    */


    return 0;
}
