#include "SimplexNoise.hpp"

/*
 Hash lookup table as defined by Ken Perlin.
 This is a randomly arranged array of all numbers from 0-255 inclusive.
*/
const std::uint8_t originalPermutation[256] = {
        151, 160, 137, 91, 90, 15, 131, 13, 201, 95, 96, 53, 194, 233, 7,
        225, 140, 36, 103, 30, 69, 142, 8, 99, 37, 240, 21, 10, 23, 190,
        6, 148, 247, 120, 234, 75, 0, 26, 197, 62, 94, 252, 219, 203, 117,
        35, 11, 32, 57, 177, 33, 88, 237, 149, 56, 87, 174, 20, 125, 136,
        171, 168, 68, 175, 74, 165, 71, 134, 139, 48, 27, 166, 77, 146, 158,
        231, 83, 111, 229, 122, 60, 211, 133, 230, 220, 105, 92, 41, 55, 46,
        245, 40, 244, 102, 143, 54, 65, 25, 63, 161, 1, 216, 80, 73, 209,
        76, 132, 187, 208, 89, 18, 169, 200, 196, 135, 130, 116, 188, 159, 86,
        164, 100, 109, 198, 173, 186, 3, 64, 52, 217, 226, 250, 124, 123, 5,
        202, 38, 147, 118, 126, 255, 82, 85, 212, 207, 206, 59, 227, 47, 16,
        58, 17, 182, 189, 28, 42, 223, 183, 170, 213, 119, 248, 152, 2, 44,
        154, 163, 70, 221, 153, 101, 155, 167, 43, 172, 9, 129, 22, 39, 253,
        19, 98, 108, 110, 79, 113, 224, 232, 178, 185, 112, 104, 218, 246, 97,
        228, 251, 34, 242, 193, 238, 210, 144, 12, 191, 179, 162, 241, 81, 51,
        145, 235, 249, 14, 239, 107, 49, 192, 214, 31, 181, 199, 106, 157, 184,
        84, 204, 176, 115, 121, 50, 45, 127, 4, 150, 254, 138, 236, 205, 93,
        222, 114, 67, 29, 24, 72, 243, 141, 128, 195, 78, 66, 215, 61, 156,
        180
};

/*
 * Pseudo random Gradients for 2D space
 * Originally 12 gradients for 3D space were used.
 * Changed it to 9 - 2D space equivalent
 */
const std::pair< double, double > gradient2D[9] = {
        std::make_pair( 1.0, 1.0 ), std::make_pair( -1.0, 1.0 ), std::make_pair( 1.0, -1.0 ),
        std::make_pair( -1.0, -1.0 ), std::make_pair( 1.0, 0.0 ), std::make_pair( -1.0, 0.0 ),
        std::make_pair( 0.0, 1.0 ), std::make_pair( 0.0, -1.0 ), std::make_pair( 1.0, -0.0 )
};

SimplexNoise::SimplexNoise() {
    std::copy( std::begin( originalPermutation ), std::end( originalPermutation ), std::begin( permutation ));
}

inline unsigned short SimplexNoise::hash( int i ) {
    return permutation[static_cast<unsigned int>(i) & 255];
}

inline int SimplexNoise::fastFloor( double x ) {
    return ( x > 0.0 ) ? ( int ) x : ( int ) ( x - 1.0 );
}

inline double SimplexNoise::dot( std::pair< double, double > gradient2D, double x, double y ) {
    return gradient2D.first * x + gradient2D.second * y;
}

/*
 Direct cpp port from java algorithm (link to source inside  hpp file)
 Returns values from range: -1 to 1
*/
double SimplexNoise::signedRawNoise( double xPos, double yPos ) {
    double nCorner0, nCorner1, nCorner2;

    // Skew the input space to determine which simplex cell we're in
    double skewedCell = ( xPos + yPos ) * skewingFactor;
    int simplexCellx = fastFloor( xPos + skewedCell );
    int simplexCelly = fastFloor( yPos + skewedCell );

    // Unskew the cell origin back to (x,y) space
    double unskewedCell = ( simplexCellx + simplexCelly ) * unskewingFactor;
    double X0 = simplexCellx - unskewedCell;
    double Y0 = simplexCelly - unskewedCell;
    double x0 = xPos - X0; // The x,y distances from the cell origin
    double y0 = yPos - Y0;

    // For the 2D case, the simplex shape is an equilateral triangle.
    // Determine which simplex we are in.
    // Offsets for second (middle) corner of simplex in (i,j) coords
    int i1, j1;
    if ( x0 > y0 ) {
        i1 = 1;
        j1 = 0;
        // lower triangle, XY order: (0,0)->(1,0)->(1,1)
    } else {
        i1 = 0;
        j1 = 1;
    } // upper triangle, YX order: (0,0)->(0,1)->(1,1)

    // A step of (1,0) in (i,j) means a step of (1-c,-c) in (x,y), and
    // a step of (0,1) in (i,j) means a step of (-c,1-c) in (x,y), where
    // c = (3-sqrt(3))/6
    // Offsets for middle corner in (x,y) unskewed coords
    double x1 = x0 - i1 + unskewingFactor;
    double y1 = y0 - j1 + unskewingFactor;
    double x2 = x0 - 1.0 + 2.0 * unskewingFactor; // Offsets for last corner in (x,y) unskewed coords
    double y2 = y0 - 1.0 + 2.0 * unskewingFactor;

    // Work out the hashed gradient2D indices of the three simplex corners
    int ii = static_cast<unsigned int> (simplexCellx) & 255u;
    int jj = static_cast<unsigned int> (simplexCelly) & 255u;

    const std::uint8_t gradientsSize = sizeof( gradient2D ) / sizeof( gradient2D[0] );
    int gradientIndex0 = hash( ii + hash( jj )) % gradientsSize;
    int gradientIndex1 = hash( ii + i1 + hash( jj + j1 )) % gradientsSize;
    int gradientIndex2 = hash( ii + 1 + hash( jj + 1 )) % gradientsSize;

    // Calculate the contribution from the three corners
    nCorner0 = calculateCornerValue( x0, y0, gradientIndex0 );
    nCorner1 = calculateCornerValue( x1, y1, gradientIndex1 );
    nCorner2 = calculateCornerValue( x2, y2, gradientIndex2 );

    // Add contributions from each corner to get the final noise value.
    // The result is scaled to return values in the interval [-1,1].
    return 70.0 * ( nCorner0 + nCorner1 + nCorner2 );
}

double SimplexNoise::unsignedRawNoise( double xPos, double yPos ) {
    return signedRawNoise( xPos, yPos ) / 2.0 + 0.5;
}

double SimplexNoise::calculateCornerValue( double x, double y, int gradientIndex ) {
    double corner = 0.0;
    double t = 0.5 - x * x - y * y;
    if ( t > 0.0 ) {
        t *= t;
        corner = t * t * dot( gradient2D[gradientIndex], x, y );
    }

    return corner;
}

void SimplexNoise::randomizeSeed() {
    unsigned int randomSeed = static_cast<long unsigned int>(time( nullptr ));
    setSeed( randomSeed );
}

void SimplexNoise::setSeed( unsigned int seedNumber ) {
    std::default_random_engine randomDevice( seedNumber );
    std::mt19937 seed( randomDevice());
    std::shuffle( std::begin( permutation ), std::end( permutation ), seed );
}

/**
 * Fractional Brownian Motion is the summation of successive octaves of noise, each with higher frequency and lower amplitude.
 *
 * @param xPos       - noise x value
 * @param yPos       - noise y value
 * @param octaves    - how many layers you are putting together (number of octaves determines how detailed the map will look)
 * @param lacunarity - Lacunarity is what makes the frequency grow as each octave the frequency is multiplied by the lacunarity
 * @param gain       - Gain, also called persistence, is what makes the amplitude shrink (or not shrink). Each octave the amplitude is multiplied by the gain

 * @return           - Fractional Brownian motion for noise value
 */
double SimplexNoise::signedFBM( double xPos, double yPos, unsigned int octaves, double lacunarity, double gain ) {
    double sum = 0;
    double frequency = 1.0;
    double amplitude = 1.0;
    double maxValue = 0;  // Used for normalizing result to -1.0 - 1.0
    for ( int i = 0; i < octaves; ++i ) {
        sum += signedRawNoise( xPos * frequency, yPos * frequency ) * amplitude;
        maxValue += amplitude;
        amplitude *= gain;
        frequency *= lacunarity;
    }

    return sum / maxValue;
}

double SimplexNoise::unsignedFBM( double xPos, double yPos, unsigned int octaves, double lacunarity, double gain ) {
    return signedFBM( xPos, yPos, octaves, lacunarity, gain ) / 2.0 + 0.5;
}