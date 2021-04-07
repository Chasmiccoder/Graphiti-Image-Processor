#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "./headers/ImageProcessing.h"
#include "./headers/stb_image.h"
#include "./headers/stb_image_write.h"


Image::Image() {
    /*
    Loads a blank image with just one blank pixel
    */
    
    size     = 3;
    width    = 1;
    height   = 1;
    channels = 3;
    
    data     = new uint8_t[ size ];
    data[0] = 255;
    data[1] = 255;
    data[2] = 255;
    pixels   = {{{255,255,255}}};

}

Image::Image( std::string filename ) {
    this->filename = filename;

            
}

bool Image::read( std::string filename ) {
    this->filename = filename;
    const char* filename_const_char = filename.c_str();

    data = stbi_load( filename_const_char, &width, &height, &channels, 0 );
    bool tranform = convertToPixelFormat(); // Initialise the image in pixel vector format 

    // If the file was not read properly, return false, else return true
    return data != NULL && tranform;
}


bool Image::convertToPixelFormat() {
    
}
