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
        void setSeed(const unsigned int &seedNumber);
        double signedFBM(const double &xPos, const double &yPos, const unsigned int &octaves, const double &lacunarity, const double &gain);
        double signedRawNoise(const double &xPos, const double &yPos);
        double unsignedFBM(const double &xPos, const double &yPos, const unsigned int &octaves, const double &lacunarity, const double &gain);
        double unsignedRawNoise(const double &xPos, const double &yPos);

    private:
        static constexpr double SKEWING_FACTOR = 0.366025; // 0.5 * ( std::sqrt( 3.0 ) - 1.0 )
        static constexpr double UNSKEWING_FACTOR = 0.211325; // ( 3.0 - std::sqrt( 3.0 )) / 6.0

        std::uint8_t permutation[256];

        double calculateCornerValue(const double &x, const double &y, const int &gradientIndex);
        double dot(std::pair< double, double > gradient2D, const double &x, const double &y);
        int fastFloor(const double &x);
        unsigned short hash(const int &i);
};

#endif // SIMPLEXNOISE_H