//
// Created by no-code-team on 11/6/18.
//

#ifndef _COLOR_HPP_
#define _COLOR_HPP_

#include <algorithm>
#include <iostream>
#include <math.h>

/**
   Représente une couleur avec un codage RGB. Ce codage utilise 3
   octets, le premier octet code l'intensité du rouge, le deuxième
   l'intensité du vert, le troisième l'intensité du bleu.
*/
struct Color {
    typedef unsigned char Byte;
    /// Code les 3 canaux RGB sur 3 octets.
    Byte red, green, blue;
    Color() {}
    /// Crée la couleur spécifiée par (_red,_green,_blue).
    Color( Byte _red, Byte _green, Byte _blue )
            : red( _red ), green( _green ), blue( _blue ) {}
    /// @return l'intensité de rouge (entre 0.0 et 1.0)
    float r() const { return static_cast<float>(( (float) red ) / 255.0); }
    /// @return l'intensité de vert (entre 0.0 et 1.0)
    float g() const { return static_cast<float>(( (float) green ) / 255.0); }
    /// @return l'intensité de bleu (entre 0.0 et 1.0)
    float b() const { return static_cast<float>(( (float) blue ) / 255.0); }
    /// Sert à désigner un canal.
    enum Channel { Red, Green, Blue };
    /// @return le canal le plus intense.
    Channel argmax() const
    {
        if ( red >= green ) return red >= blue ? Red : Blue;
        else                return green >= blue ? Green : Blue;
    }
    /// @return l'intensité maximale des canaux
    float max() const { return std::max( std::max( r(), g() ), b() ); }
    /// @return l'intensité minimale des canaux
    float min() const { return std::min( std::min( r(), g() ), b() ); }
    /**
       Convertit la couleur RGB en le modèle HSV (TSV en français).
       @param h la teinte de la couleur (entre 0 et 359), hue en anglais.
       @param s la saturation de la couleur (entre 0.0 et 1.0)
       @param v la valeur ou brillance de la couleur (entre 0.0 et 1.0).
    */
    void getHSV( int & h, float & s, float & v ) const
    {
        // Taking care of hue
        if ( max() == min() ) h = 0;
        else {
            switch ( argmax() ) {
                case Red:   h = ( (int) ( 60.0 * ( g() - b() ) / ( max() - min() ) + 360.0 ) ) % 360;
                    break;
                case Green: h = ( (int) ( 60.0 * ( b() - r() ) / ( max() - min() ) + 120.0 ) );
                    break;
                case Blue:  h = ( (int) ( 60.0 * ( r() - g() ) / ( max() - min() ) + 240.0 ) );
                    break;
            }
        }
        // Taking care of saturation
        s = static_cast<float>(max() == 0.0 ? 0.0 : 1.0 - min() / max());
        // Taking care of value
        v = max();
    }
    /**
       Convertit la couleur donnée avec le modèle HSV (TSV en français) en une couleur RGB.
    */
    void setHSV( int h, float s, float v ) {

        double c = h * s;
        double h_prime = h / 60;
        double x = c * (1.0 - fabs((fmod(h_prime, 2.0) - 1.0)));
        double m = v - c;
        double r_prime, g_prime, b_prime;
        if (0 <= h_prime and h_prime < 60){
            r_prime = c;
            g_prime = x;
            b_prime = 0;
        }
        else if (60 <= h_prime and h_prime < 120){
            r_prime = x;
            g_prime = c;
            b_prime = 0;
        }
        else if (120 <= h_prime and h_prime < 180){
            r_prime = 0;
            g_prime = c;
            b_prime = x;
        }
        else if (180 <= h_prime and h_prime < 240){
            r_prime = 0;
            g_prime = x;
            b_prime = c;
        }
        else if (240 <= h_prime and h_prime < 300){
            r_prime = x;
            g_prime = 0;
            b_prime = c;
        } else{
            r_prime = c;
            g_prime = 0;
            b_prime = x;
        }
        // Normalisation des piwel entre 0 et 255
        red = static_cast<Byte>((r_prime + m) * 255.0);
        green = static_cast<Byte>((g_prime + m) * 255.0);
        blue = static_cast<Byte>((b_prime + m) * 255.0);
    }

    /// Operateur de flux entrée pour ajouter les pixel de couleur
    friend std::istream & operator>>(std::istream & input, Color & c){
        Byte r, g, b;
        input >> r >> g >> b;
        c = Color(r, g, b);
        return input;
    }
};
#endif //_COLOR_HPP_