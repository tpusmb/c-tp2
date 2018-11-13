//
// Created by no-code-team on 11/13/18.
//
#include "Image2D.h"
#include "Color.hpp"
#include "Image2DWriter.h"
#include "Image2DReader.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <math.h>

/**
 * Script to equalize all the pixal of an image
 */

using namespace std;
int main( int argc, char** argv )
{
    typedef Image2D<Color> ColorImage2D;
    typedef ColorImage2D::Iterator Iterator;
    typedef ColorImage2D::ConstIterator ConstIterator;

    if ( argc < 3 )
    {
        std::cerr << "Usage: invert-red-blue <input.pgm> <output.pgm>" << std::endl;
        return 0;
    }

    ColorImage2D img;
    std::ifstream input( argv[1] );
    bool ok2 = Image2DReader<Color>::read( img, input, false );
    if ( !ok2 ) {
        std::cerr << "Error read input file." << std::endl;
        return 1;
    }

    for(auto & c:img){
        unsigned char r, g, b;
        r = c.red;
        g = c.green;
        b = c.blue;
       c = Color(b, g, r);
    }

    std::ofstream output( argv[2]);
    ok2 = Image2DWriter<Color>::write( img, output, false );
    if ( !ok2 ) {
        std::cerr << "Error writing output file." << std::endl;
        return 1;
    }
}

