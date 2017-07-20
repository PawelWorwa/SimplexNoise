/**
 * Simple Noise
 *
 * Algorithm taken from          : http://webstaff.itn.liu.se/~stegu/simplexnoise/SimplexNoise.java
 * PDF version (with description): http://staffwww.itn.liu.se/~stegu/simplexnoise/simplexnoise.pdf
 * Octaves algorithm             : http://flafla2.github.io/2014/08/09/perlinnoise.html
 */

#ifndef SIMPLEXNOISE_H
#define SIMPLEXNOISE_H

#include <algorithm>
#include <cmath>
#include <random>

class SimplexNoise {
    public:
        SimplexNoise();
        virtual ~SimplexNoise();

        float noise ( float xPos, float yPos );
        float octave( int octaves, float xPos, float yPos );
        void  randomizeSeed ( void );
        float unsignedNoise ( float xPos, float yPos );
        float unsignedOctave( int octaves, float xPos, float yPos );

    private:
        class Gradient {
            public:
                float x, y;

                Gradient( float x, float y ) {
                    this->x = x;
                    this->y = y;
                }
        }; /* for sake of one class purpose only */

        static const Gradient       gradient[];
        static const unsigned short originalPermTab[256];
        static const float          skewingFactor;
        unsigned short              permTab[256];
        static const float          unskewingFactor;

        float          calculateCornerValue( float x, float y, int gradientIndex );
        float          dot( Gradient gradient, float xPos, float yPos );
        int            fastfloor( float x );
        unsigned short hash ( int i );
};

#endif // SIMPLEXNOISE_H
