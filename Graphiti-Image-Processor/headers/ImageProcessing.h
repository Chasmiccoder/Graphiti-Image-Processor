#pragma once

// To use uint8_t
#include <stdint.h>

// To store the image in a more refined / easily usable format
#include <vector>

class Image {
    private:
        // Stores the image data in raw pixel format
        uint8_t* data;

        // Stores the image data in cleaner format
        std::vector< std::vector<uint8_t> > pixels;

        // Stores the size of the image (width * height * channels)
        size_t size;

        int width;
        int height;
        int channels;

        /*
        What are channels?
        A channel can be thought of as a layer in the image, which consists the grayscale image
        along one of the primary colours. For example, an RGB image has 3 channels corresponding to
        the colours Red, Green, and Blue. 
        A 24 Bit RGB Image (which is the industry standard) has three 8 bit channels
        CMYK (cyan, magenta, yellow, black) is an example with 4 channels.
        */


    public:
        Image() {
            data     = NULL;
            pixels   = {{0,0,0}}; // Just one black pixel
            size     = 0;
            width    = 0;
            height   = 0;
            channels = 0;
        }
     

};