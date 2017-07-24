/**
 * Simple Noise Generator Library
 *
 * Algorithm taken from          : http://webstaff.itn.liu.se/~stegu/simplexnoise/SimplexNoise.java
 * PDF version (with description): http://staffwww.itn.liu.se/~stegu/simplexnoise/simplexnoise.pdf
 * Octaves (Fractal) algorithm   : http://flafla2.github.io/2014/08/09/perlinnoise.html
 */

#ifndef SIMPLEXNOISE_H
#define SIMPLEXNOISE_H

#include <algorithm>
#include <cmath>
#include <random>

class SimplexNoise {
    public:
        explicit SimplexNoise();
        virtual ~SimplexNoise();

        void  randomizeSeed ( void );
        void  setFrequency  ( float frequency ) { this->frequency = frequency; };
        void  setOctaves    ( int octaves ) { this->octaves = octaves; };
        void  setPersistence( float persistence ) { this->persistence = persistence; };
        float signedOctave  ( float xPos, float yPos );
        float unsignedOctave( float xPos, float yPos );

    private:
        float frequency;
        static const std::pair<float, float> gradient[12];
        unsigned int                         octaves;
        static const unsigned short          originalPermTab[256];
        unsigned short                       permTab[256];
        float                                persistence;
        static const float                   skewingFactor;
        static const float                   unskewingFactor;

        float          noise ( float xPos, float yPos );
        float          calculateCornerValue( float x, float y, int gradientIndex );
        float          dot( std::pair<float, float> gradient, float xPos, float yPos );
        int            fastfloor( float x );
        unsigned short hash ( int i );
};

#endif // SIMPLEXNOISE_H
