#include <cmath>
#include <iostream>
#include <fstream>
#include "Image2D.h"
#include "Image2DReader.h"
#include "Image2DWriter.h"
#include "Accessor.h"
#include "Histogramme.h"

int main( int argc, char** argv )
{
    typedef Image2D<Color> ColorImage2D;
    typedef Image2DReader<Color> ColorImage2DReader;
    typedef Image2DWriter<Color> ColorImage2DWriter;
    typedef ColorImage2D::Iterator ColorIterator;
    if ( argc < 3 )
    {
        std::cerr << "Usage: egaliseur-couleur <input.ppm> <output.pgm>" << std::endl;
        return 0;
    }
    ColorImage2D img;
    std::ifstream input( argv[1] ); // récupère le 1er argument.
    bool ok = ColorImage2DReader::read( img, input, false );
    if ( !ok )
    {
        std::cerr << "Error reading input file." << std::endl;
        return 1;
    }
    input.close();

    Histogramme H;
    H.init(img.begin<ColorValueAccessor>(), img.end<ColorValueAccessor>());

    // egalisation
    for (auto it = img.begin<ColorValueAccessor>(), itE = img.end<ColorValueAccessor>(); it != itE; it++){
        *it = H.egalisation(*it);
    }
    std::ofstream output( argv[2] ); // récupère le 2eme argument.
    bool ok2 = ColorImage2DWriter::write( img, output, false );
    if ( !ok2 )
    {
        std::cerr << "Error writing output file." << std::endl;
        return 1;
    }
    output.close();
    return 0;
}