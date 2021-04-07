#pragma once

// To use uint8_t (unsigned integer of exactly 8 bits)
#include <stdint.h>

// To store the image in a more refined / easily usable format
#include <vector>

#include <string>

class Image {
    private:
        // Stores the image data in raw pixel format
        uint8_t* data = NULL;

        // Stores the image data in cleaner format
        //Each element pixels[i][j] is a vector with the RGB values {R,G,B} 
        std::vector< std::vector< std::vector<uint8_t> > > pixels;

        // Stores the size of the image (width * height * channels)
        size_t size;

        int width;
        int height;
        int channels;

        std::string filename;

        /*
        What are channels?
        A channel can be thought of as a layer in the image, which consists the grayscale image
        along one of the primary colours. For example, an RGB image has 3 channels corresponding to
        the colours Red, Green, and Blue. 
        A 24 Bit RGB Image (which is the industry standard) has three 8 bit channels
        CMYK (cyan, magenta, yellow, black) is an example with 4 channels.
        */


    public:
        Image();                                       // Default constructor to load a blank image (1 pixel)
        Image( std::string filename );                 // Constructor to load an image with given filename
        Image( int width, int height, int channels );  // Constructor to load a blank image with given dimensions
        Image( const Image& img );                     // Copy constructor to copy an existing image

        ~Image(); // Destructor to free the allocated memory

        bool read( std::string filename );     // Reads image data from a specified file 
        bool write( std::string filename );    // Writes image data to a new file, with its specified filename

        bool convertRawImageToPixelFormat();   // Converts an image from raw image format to pixel vector format
        bool convertPixelFormatToRawImage();   // Converts an image from pixel vector format to raw image format


    // Add function for convesion of 'data' to 'pixels'     

};