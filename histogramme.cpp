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
    typedef ColorImage2D::Iterator ColorIterator;
    if ( argc < 3 )
    {
        std::cerr << "Usage: histogramme <input.ppm> <output.pgm>" << std::endl;
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


    typedef Image2D<unsigned char> GrayLevelImage2D;
    typedef Image2DWriter<unsigned char> GrayLevelImage2DWriter;
    typedef GrayLevelImage2D::Iterator GrayLevelIterator;
    // Make histogram image 256 because we scall the histogramme value between 0 and 255
    // 255 * 2 because we need to put tow histogram the +25 is to leave space between the histograms
    GrayLevelImage2D img2( (360 * 2) + 25, 255);

    int x = 0;
    // histogramme
    for (auto & c:H.hist()){
        for(int y = 255; y >= 255 - c; y--){
            *img2.start(x, y) = 255;
        }
        x++;
    }

    x+=25;

    for (auto & c:H.hist_cumul()){
        int end_value = static_cast<int>(round(c * 255.0));
        for(int y = 255; y >= end_value; y--){
            *img2.start(x, y) = 255;
        }
        x++;
    }
    std::ofstream output( argv[2] ); // récupère le 2eme argument.
    bool ok2 = GrayLevelImage2DWriter::write( img2, output, false );
    if ( !ok2 )
    {
        std::cerr << "Error writing output file." << std::endl;
        return 1;
    }
    output.close();
    return 0;
}