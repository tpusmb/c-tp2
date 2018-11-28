//
// Created by no-code-team on 11/13/18.
//

#ifndef TP2_C_IMAGE2DREADER_H
#define TP2_C_IMAGE2DREADER_H

#include <iostream>
#include <string>
#include "Color.hpp"
#include "Image2D.h"
template <typename TValue>
class Image2DReader {
public:
    typedef TValue Value;
    typedef Image2D<Value> Image;
    static bool read( Image & img, std::istream & input, bool ascii )
    {
        std::cerr << "[Image2DReader<TValue>::read] NOT IMPLEMENTED." << std::endl;
        return false;
    }
};
/// Specialization for gray-level images.
template <>
class Image2DReader<unsigned char> {
public:
    typedef unsigned char Value;
    typedef Image2D<Value> Image;
    static bool read( Image & img, std::istream & input, bool ascii )
    {
        // teste si tout va bien
        if (!input.good()){
            std::cerr << "Le fichier donner n'est pas valide !";
            return false;
        }

        std::string line;
        // 1 - On passe le premiere ligne
        std::getline(input, line);

        // On se mais sur la ligne commenter
        std::getline(input, line);
        // 2- on lie le deuxieme
        // 3 - on parcour les ligne tant que c'est des commentaire
        while (line[0] == '#')
            std::getline(input, line);
        // 4 - On recupaire le hauteur est la largeur
        std::istringstream istr(line);

        int width, height;
        istr >> width >> height;
        img = Image(width, height, 0);
        // on passe a la ligne suivant
        std::getline(input, line);
        std::istringstream istr2(line);
        int pix_val = 0;
        istr2 >> pix_val;
        // std::getline(input, line);
        Image::Iterator m_data_iterator = img.begin();
        input >> std::noskipws;
        // Parcoure du fichier
        while (!input.eof()){
            Value g;
            // on recupaire le gray level
            input >> g;
            // on l'ajout a notre obj m-data via l'iterateur
            *m_data_iterator++ = g;
        }
        return true;
    }
};
/// Specialization for color images.
template <>
class Image2DReader<Color> {
public:
    typedef Color Value;
    typedef Image2D<Value> Image;
    typedef Image::Iterator Iterator;
    static bool read( Image & img, std::istream & input, bool ascii )
    {
        // teste si tout va bien
        if (!input.good()){
            std::cerr << "Le fichier donner n'est pas valide !";
            return false;
        }

        std::string line;
        // 1 - On passe le premiere ligne
        std::getline(input, line);

        // On se mais sur la ligne commenter
        std::getline(input, line);
        // 2- on lie le deuxieme
        // 3 - on parcour les ligne tant que c'est des commentaire
        while (line[0] == '#')
            std::getline(input, line);
        // 4 - On recupaire le hauteur est la largeur
        std::istringstream istr(line);

        int width, height;
        istr >> width >> height;
        img = Image(width, height, Color( 0, 0, 0 ));
        // on passe a la ligne suivant
        std::getline(input, line);
        std::istringstream istr2(line);
        int pix_val = 0;
        istr2 >> pix_val;
        // std::getline(input, line);
        Iterator m_data_iterator = img.begin();
        input >> std::noskipws;
        // Parcoure du fichier
        Color c;
        while (!input.eof()){
            // on recupaire le gray level
            input >> c;
            // on l'ajout a notre obj m-data via l'iterateur
            *m_data_iterator++ = c;
        }
        return true;
    }
};

#endif //TP2_C_IMAGE2DREADER_H
