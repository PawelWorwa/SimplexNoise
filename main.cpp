/**
 * For noise test and visualisation
 */
#include <SFML/Graphics.hpp>

#include <cstdlib>
#include <ctime>

#include "SimplexNoise.hpp"

/* ***** Variables *****/
unsigned static int const width  = 400;
unsigned static int const height = 400;
std::vector<sf::VertexArray> noiseVisualisation;

/* ***** Functions *****/
void generateNoise( void ) {
    SimplexNoise noiseGenerator;
    noiseGenerator.randomizeSeed();

    for ( std::size_t x=0; x<width; ++x ) {
        for ( std::size_t y=0; y<height; ++y ) {
            float xPos = float( x ) / float( width )  - 0.5f;
            float yPos = float( y ) / float( height ) - 0.5f;

            //float freq = 2.0f;
            //float elevation = noiseGenerator.unsignedNoise( freq*xPos, freq*yPos );
            int octaves     = 5;
            float elevation = noiseGenerator.unsignedOctave( octaves, xPos, yPos );

            sf::Color color = sf::Color( elevation*255, elevation*255, elevation*255 );
            sf::VertexArray point( sf::Points, 1 );
            point[0].position = sf::Vector2f( x, y );
            point[0].color = color;

            noiseVisualisation.push_back( point );
        }
    }
}
/* ***** Main *****/
int main() {
    srand( time(0) );
    sf::RenderWindow window( sf::VideoMode(width, height), "Simplex Noise 2D visualisation" );

    generateNoise();

    while ( window.isOpen() ) {
        sf::Event event;
        while ( window.pollEvent(event) ) {
            if ( event.type == sf::Event::Closed ) {
                window.close();
            }
        }

        for( std::size_t i=0; i<noiseVisualisation.size(); ++i ) {
            sf::VertexArray point = noiseVisualisation.at( i );
            window.draw( point );
        }

        window.display();
    }

    return EXIT_SUCCESS;
}
