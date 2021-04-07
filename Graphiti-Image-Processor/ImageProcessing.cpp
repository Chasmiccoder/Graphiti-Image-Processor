#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "./headers/ImageProcessing.h"
#include "./headers/stb_image.h"
#include "./headers/stb_image_write.h"


Image::Image() {
    /*
    Allocates a blank image with just one blank pixel
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
    /*
    Reads the specified file using the read() method,
    and allocates the pixels of the image
    */
    
    bool read_status = read( filename );
    
    if ( read_status ) {
        printf( "Successfully read file: " );
        std::cout << filename << std::endl;
        size = width * height * channels;
    }

    else {
        printf( "Failed to read file: " );
        std::cout << filename << std::endl;
    }
            
}


Image::Image( int width, int height, int channels ) : width(width), height(height), channels(channels) {
    /*
    Allocates an empty image with specified width, height, and number of channels
    */
    
    size = width * height * channels;
    data = new uint8_t[ size ];
    bool transform = convertRawImageToPixelFormat();

}


Image::Image( const Image& img ) : Image( img.width, img.height, img.channels ) {
    /*
    Copy constructor that helps copy one image to another
    Useful for image manipulation, since the original image remains unaffected
    */
    
    memcpy( data, img.data, size );
    bool transform = convertRawImageToPixelFormat();

}


Image::~Image() {
    /*
    Default destructor that frees the memory used by the image
    */
    
    // To free the raw image
    stbi_image_free( data );
    
    // We do not need to free the image in pixel vector format, since the compiler ensures that the vector
    // will get freed after use
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
    int iterator = 0;

    for ( int i = 0; i < height; i++ ) {
        for ( int j = 0; j < width; j++ ) {
            for ( int k = 0; k < channels; k++ ) {
                *( data + iterator ) = pixels[i][j][k];  
                iterator++;
            }
        }
    }

    // Something went wrong
    if ( data == NULL ) {
        return false;
    }
    return true;

}
