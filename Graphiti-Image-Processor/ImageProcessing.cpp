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
    pixels = img.pixels;

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


Image::ImageType Image::getFileType( std::string filename ) {
    /*
    Takes an input string and returns the format of the image
    Currently supported formats: .jpg, .png, .bmp, .tga
    */
    
    int length = filename.length();
    std::string fileFormat = "";
    for ( int i = length - 1; i >= 0; i-- ) {
        std::string character = filename.substr( i,1 );
        if ( character == "." ) {
            fileFormat = filename.substr( i + 1, length- i - 1 );
            break;
        }
    }

    if ( fileFormat == "jpg" ) {
        return ImageType_JPG;
    }
        
    else if ( fileFormat == "png" ) {
        return ImageType_PNG;
    }

    else if ( fileFormat == "bmp" ) {
        return ImageType_BMP;
    }

    else if ( fileFormat == "tga" ) {
        return ImageType_TGA;
    }

    // If there is an issue with the filename that has been input, just convert it to .png
    else {
        return ImageType::ImageType_PNG;
    }

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
    //return data != NULL && tranform;
    return data != NULL;
}


bool Image::write( std::string filename ) {
    /*
    The image gets converted back to its raw image format from the pixel vector format, 
    after which it gets written to a file
    */

    // Save changes made in pixel vector image to the raw image 
    bool transform = convertPixelFormatToRawImage();
    if ( transform == false ) {
        printf( "Error while writing image!\n" );
        return false;
    }
    
    ImageType type = getFileType( filename );
    const char* filename_const_char = filename.c_str();
    int success;

    switch( type ) {
        case ImageType_JPG:
            success = stbi_write_jpg( filename_const_char, width, height, channels, data, 100 );
            break;
        
        case ImageType_PNG:
            // The last argument is stride_in_bytes, which is the product of the width and the number of channels
            success = stbi_write_png( filename_const_char, width, height, channels, data, width * channels );
            break;
        
        case ImageType_BMP:
            success = stbi_write_bmp( filename_const_char, width, height, channels, data );
            break;
        
        case ImageType_TGA:
            success = stbi_write_tga( filename_const_char, width, height, channels, data );
            break;

    }

    // If success is 0, then something went wrong and the file did not get written properly
    return success != 0;

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
        std::vector< std::vector<int> > pixel_row;

        for ( int j = 0; j < width; j++ ) {
            std::vector< int > pixel;

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
                //*( data + iterator ) = pixels[i][j][k];  
                memset( data + iterator, pixels[i][j][k], 1 );
                iterator++;
            }
        }
    }

    // If something went wrong
    if ( data == NULL ) {
        return false;
    }
    return true;

}
