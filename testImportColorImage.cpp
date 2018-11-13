// file testColorImage2D.cpp
#include <iostream>
#include <fstream>
#include "Image2D.h"
#include "Color.hpp"
#include "Image2DWriter.h"
#include "Image2DReader.h"

int main()
{
    typedef Image2D<Color> ColorImage2D;
    typedef ColorImage2D::Iterator Iterator;
    typedef ColorImage2D::ConstIterator ConstIterator;
    ColorImage2D img;
    std::ifstream input("colors.ppm");
    bool ok2 = Image2DReader<Color>::read( img, input, false );
    if ( !ok2 ) {
        std::cerr << "Error writing output file." << std::endl;
        return 1;
    }
    std::ofstream output( "colors2.ppm" );
    ok2 = Image2DWriter<Color>::write( img, output, false );
    if ( !ok2 ) {
        std::cerr << "Error writing output file." << std::endl;
        return 1;
    }
    output.close();
    return 0;
}
