/**
 * Simple Noise Generator Library
 *
 * Algorithm taken from          : http://webstaff.itn.liu.se/~stegu/simplexnoise/SimplexNoise.java
 * PDF version (with description): http://staffwww.itn.liu.se/~stegu/simplexnoise/simplexnoise.pdf
 * Octaves (Fractal) algorithm   : http://flafla2.github.io/2014/08/09/perlinnoise.html
 * Fractional Brownian Motion    : https://www.scratchapixel.com/lessons/procedural-generation-virtual-worlds/procedural-patterns-noise-part-1/simple-pattern-examples
 *
 * Bonus: good tutorial how to generate terrain from noise
 * https://www.redblobgames.com/maps/terrain-from-noise/
 */

#ifndef SIMPLEXNOISE_H
#define SIMPLEXNOISE_H

#include <algorithm>
#include <cmath>
#include <ctime>
#include <random>

class SimplexNoise {
    public:
        explicit SimplexNoise();

        void randomizeSeed();
        void setSeed( unsigned int seedNumber );

        double signedRawNoise( double xPos, double yPos );
        double unsignedRawNoise( double xPos, double yPos );
        double signedFBM( double xPos, double yPos, unsigned int octaves, double lacunarity, double gain );
        double unsignedFBM( double xPos, double yPos, unsigned int octaves, double lacunarity, double gain );

    private:
        const double skewingFactor = 0.366025;   // 0.5 * ( std::sqrt( 3.0 ) - 1.0 )
        const double unskewingFactor = 0.211325; // ( 3.0 - std::sqrt( 3.0 )) / 6.0
        std::uint8_t permutation[256];

        double calculateCornerValue( double x, double y, int gradientIndex );
        double dot( std::pair< double, double > gradient2D, double x, double y );
        int fastFloor( double x );
        unsigned short hash( int i );
};

#endif // SIMPLEXNOISE_H