#include "SimplexNoise.hpp"

SimplexNoise::SimplexNoise() {
    octaves = 1;
    frequency = 1.0f;
    persistence = 0.5f;

    std::copy( std::begin(originalPermTab), std::end(originalPermTab), std::begin(permTab) );
}

SimplexNoise::~SimplexNoise() {
}

unsigned short SimplexNoise::hash( int i ) {
    return permTab[i & 255];
}

const float SimplexNoise::skewingFactor   = 0.5f * ( sqrt(3.0f) - 1.0f );
const float SimplexNoise::unskewingFactor = ( 3.0f - sqrt(3.0f) ) / 6.0f;

/*
 Hash lookup table as defined by Ken Perlin.
 This is a randomly arranged array of all numbers from 0-255 inclusive.
*/
const unsigned short SimplexNoise::originalPermTab[256] = {
    151, 160, 137, 91,  90,  15,  131, 13,  201, 95,  96,  53,  194, 233, 7,
    225, 140, 36,  103, 30,  69,  142, 8,   99,  37,  240, 21,  10,  23,  190,
    6,   148, 247, 120, 234, 75,  0,   26,  197, 62,  94,  252, 219, 203, 117,
    35,  11,  32,  57,  177, 33,  88,  237, 149, 56,  87,  174, 20,  125, 136,
    171, 168, 68,  175, 74,  165, 71,  134, 139, 48,  27,  166, 77,  146, 158,
    231, 83,  111, 229, 122, 60,  211, 133, 230, 220, 105, 92,  41,  55,  46,
    245, 40,  244, 102, 143, 54,  65,  25,  63,  161, 1,   216, 80,  73,  209,
    76,  132, 187, 208, 89,  18,  169, 200, 196, 135, 130, 116, 188, 159, 86,
    164, 100, 109, 198, 173, 186, 3,   64,  52,  217, 226, 250, 124, 123, 5,
    202, 38,  147, 118, 126, 255, 82,  85,  212, 207, 206, 59,  227, 47,  16,
    58,  17,  182, 189, 28,  42,  223, 183, 170, 213, 119, 248, 152, 2,   44,
    154, 163, 70,  221, 153, 101, 155, 167, 43,  172, 9,   129, 22,  39,  253,
    19,  98,  108, 110, 79,  113, 224, 232, 178, 185, 112, 104, 218, 246, 97,
    228, 251, 34,  242, 193, 238, 210, 144, 12,  191, 179, 162, 241, 81,  51,
    145, 235, 249, 14,  239, 107, 49,  192, 214, 31,  181, 199, 106, 157, 184,
    84,  204, 176, 115, 121, 50,  45,  127, 4,   150, 254, 138, 236, 205, 93,
    222, 114, 67,  29,  24,  72,  243, 141, 128, 195, 78,  66,  215, 61, 156,
    180
};
/* Pseudo random Gradients for 2D space */
const std::pair<float, float> SimplexNoise::gradient[12] = {
    std::make_pair( -1.0f, -1.0f ), std::make_pair( -1.0f, 0.0f ), std::make_pair( -1.0f, 0.0f ),
    std::make_pair( -1.0f, 1.0f ),  std::make_pair( 0.0f, -1.0f ), std::make_pair( 0.0f, -1.0f ),
    std::make_pair( 0.0f, 1.0f ),   std::make_pair( 0.0f, 1.0f ),  std::make_pair( 1.0f, -1.0f ),
    std::make_pair( 1.0f, 0.0f ),   std::make_pair( 1.0f, 0.0f ),  std::make_pair( 1.0f , 1.0f )
};

int SimplexNoise::fastfloor( float x ) {
    return ( x>0 ) ? (int)x : (int)x - 1;
}

float SimplexNoise::dot( std::pair<float, float> gradient, float x, float y ) {
    float gradX = gradient.first;
    float gradY = gradient.second;
    return gradX * x + gradY * y;
}

/*
 Direct cpp port from java algorithm mentioned earlier (link to source inside  hpp file)
 Returns values from range: -1 to 1
*/
float SimplexNoise::noise( float xPos, float yPos ) {
    float nCorner0, nCorner1, nCorner2;

    // Skew the input space to determine which simplex cell we're in
    float skewedCell = ( xPos + yPos ) * skewingFactor;
    int simplexCellx = fastfloor( xPos + skewedCell );
    int simplexCelly = fastfloor( yPos + skewedCell );

    // Unskew the cell origin back to (x,y) space
    float unskewedCell = ( simplexCellx + simplexCelly ) * unskewingFactor;
    float X0 = simplexCellx - unskewedCell;
    float Y0 = simplexCelly - unskewedCell;
    float x0 = xPos - X0; // The x,y distances from the cell origin
    float y0 = yPos - Y0;

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
    float x1 = x0 - i1 + unskewingFactor;
    float y1 = y0 - j1 + unskewingFactor;
    float x2 = x0 - 1.0f + 2.0f * unskewingFactor; // Offsets for last corner in (x,y) unskewed coords
    float y2 = y0 - 1.0f + 2.0f * unskewingFactor;

    // Work out the hashed gradient indices of the three simplex corners
    int ii = simplexCellx & 255;
    int jj = simplexCelly & 255;

    int gradientIndex0 = hash( ii + hash(jj) ) % 12;
    int gradientIndex1 = hash( ii + i1 + hash(jj + j1) ) % 12;
    int gradientIndex2 = hash( ii + 1 + hash(jj + 1) ) % 12;

    // Calculate the contribution from the three corners
    nCorner0 = calculateCornerValue( x0, y0, gradientIndex0 );
    nCorner1 = calculateCornerValue( x1, y1, gradientIndex1 );
    nCorner2 = calculateCornerValue( x2, y2, gradientIndex2 );

    // Add contributions from each corner to get the final noise value.
    // The result is scaled to return values in the interval [-1,1].
    return 70.0f * ( nCorner0 + nCorner1 + nCorner2 );
}

float SimplexNoise::signedOctave( float xPos, float yPos ) {
    float amplitude = 1.0f;
    float maxValue  = 0.0f;
    float tmpFrequency = frequency;
    float total = 0.0f;

    for( std::size_t i=0; i<octaves; ++i ) {
        total += noise( xPos * tmpFrequency, yPos * tmpFrequency ) * amplitude;
        maxValue += amplitude;
        amplitude *= persistence;
        tmpFrequency *= 2;
    }

    return total/maxValue;
}

float SimplexNoise::calculateCornerValue( float x, float y, int gradientIndex ) {
    float corner = 0.0f;
    float t = 0.5f - x * x - y * y;
    if ( t > 0 ) {
        t *= t;
        corner = t * t * dot( gradient[gradientIndex], x, y );
    }

    return corner;
}

float SimplexNoise::unsignedOctave( float xPos, float yPos ) {
    return signedOctave( xPos, yPos ) / 2 + 0.5f;
}

void SimplexNoise::randomizeSeed( void ) {
    std::random_shuffle( std::begin(permTab), std::end(permTab) );
}
