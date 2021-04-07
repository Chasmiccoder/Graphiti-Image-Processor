// Compile:
// g++ main.cpp ImageProcessing.cpp -o "ImageProcessor"
#include <iostream>

#include "./headers/ImageProcessing.h"

int main() {

    /*
    // Image Format Conversion! [Passed all checks!]
    std::string filename, formatType, newfilename;
    printf( "Enter the name of the image to be processed: " );
    std::cin >> filename;

    filename = "input-images/" + filename;

    
    printf( "Image Format Conversion (jpg, png, bmp, tga):\n" );
    std::cin >> formatType;

    printf( "Enter name of the converted image: " );
    std::cin >> newfilename;

    newfilename = "output-images/" + newfilename + "." + formatType;

    Image img1( filename );
    Image img2 = img1;
    img2.write( newfilename );
    */


    printf( "\n\n=================\n" );
    printf( "Process Complete!\n" );
    printf( "Thank you for using Graphiti\n\n" );

    char exit_char;
    printf( "Enter any character to exit:\n" );
    std::cin >> exit_char;
    // Set up tasks.json later

    return 0;
}