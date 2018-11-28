//
// Created by no-code-team on 11/6/18.
//

#ifndef TP2_C_IMAGE2DWRITER_H
#define TP2_C_IMAGE2DWRITER_H

#include <iostream>
#include <string>
#include "Color.hpp"
#include "Image2D.h"
template <typename TValue>
class Image2DWriter {
public:
    typedef TValue Value;
    typedef Image2D<Value> Image;
    static bool write( Image & img, std::ostream & output, bool ascii )
    {
        std::cerr << "[Image2DWriter<TValue>::write] NOT IMPLEMENTED." << std::endl;
        return false;
    }
};
/// Specialization for gray-level images.
template <>
class Image2DWriter<unsigned char> {
public:
    typedef unsigned char Value;
    typedef Image2D<Value> Image;
    static bool write( Image & img, std::ostream & output, bool ascii )
    {
        if (!output.good()){
            std::cerr << "Le fichier donner n'est pas valide !";
            return false;
        }
        if(ascii)
            output << "P2\n";
        else
            output << "P5\n";

        output << img.w() << ' ' << img.h() << '\n' << "255\n";
        for (Image::Iterator it = img.begin(), itE = img.end(); it != itE; ++it ) {
            if (ascii)
                output << (int) *it << ' ';
            else
                output << *it;
        }
        return true;
    }
};
/// Specialization for color images.
template <>
class Image2DWriter<Color> {
public:
    typedef Color Value;
    typedef Image2D<Value> Image;
    typedef Image::ConstIterator ConstIterator;
    static bool write( Image & img, std::ostream & output, bool ascii )
    {
        if (!ascii)
            output << "P6" << std::endl; // PPM raw
        else
            output << "P3" << std::endl;
        output << img.w() << " " << img.h() << std::endl;
        output << "255" << std::endl;
        const Image& cimg = img; // Vue "constante" sur l'image img.
        for ( ConstIterator it = cimg.begin(), itE = cimg.end(); it != itE; ++it ) // (*)
        {
            Color c = *it;
            if (!ascii)
                output << c.red << c.green << c.blue;
            else
                output << c.red << ' ' << c.green << ' ' << c.blue << ' ';
        }
        return true;
    }
};

#endif //TP2_C_IMAGE2DWRITER_H
