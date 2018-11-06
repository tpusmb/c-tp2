// file testColorImage2D.cpp
#include <iostream>
#include <fstream>
#include "Image2D.h"
#include "Color.hpp"
#include "Image2DWriter.h"

int main()
{
    typedef Image2D<Color> ColorImage2D;
    typedef ColorImage2D::Iterator Iterator;
    typedef ColorImage2D::ConstIterator ConstIterator;
    ColorImage2D img( 256, 256, Color( 0, 0, 0 ) );
    Iterator ite = img.begin();
    for ( int y = 0; y < 256; ++y )
        for ( int x = 0; x < 256; ++x )
        {
            *ite++ = Color(static_cast<Color::Byte>(y), static_cast<Color::Byte>(x),
                    static_cast<Color::Byte>((2 * x + 2 * y) % 256));
        }
    std::ofstream output( "colors.ppm" );
    bool ok2 = Image2DWriter<Color>::write( img, output, false );
    if ( !ok2 ) {
        std::cerr << "Error writing output file." << std::endl;
        return 1;
    }
    output.close();
    return 0;
}
