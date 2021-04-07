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
    /*
    The image gets read and stored in raw image format (uint8_t* data), and then stored in pixel vector format,
    after which we can easily manipulate it
    */
    
    this->filename = filename;
    const char* filename_const_char = filename.c_str();

    data = stbi_load( filename_const_char, &width, &height, &channels, 0 );
    bool tranform = convertRawImageToPixelFormat(); // Initialise the image in pixel vector format 

    // If the file was not read properly, return false, else return true
    return data != NULL && tranform;
}

bool Image::write( std::string filename ) {
    /*
    The image gets converted back to its raw image format from the pixel vector format, 
    after which it gets written to a file

    */

}


bool Image::convertRawImageToPixelFormat() {
    /*
    Converts all the image data to pixel vector format (which can be used to manipulate the image easily)
    */
    
    if ( data == NULL ) {
        return false;
    }

    int iterator = 0;

    for ( int i = 0; i < height; i++ ) {
        std::vector< std::vector<uint8_t> > pixel_row;

        for ( int j = 0; j < width; j++ ) {
            std::vector< uint8_t > pixel;

            for ( int k = 0; k < channels; k++ ) {
                pixel.push_back( *(data + iterator) );
                iterator++;
            }

            pixel_row.push_back( pixel );

        }

        pixels.push_back( pixel_row );
    }

    return true;

}


bool Image::convertPixelFormatToRawImage() {

}
