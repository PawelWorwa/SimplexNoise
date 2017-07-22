/**
 * For noise test and visualisation
 */
#include <SFML/Graphics.hpp>

#include <cstdlib>
#include <ctime>

#include "SimplexNoise.hpp"

/* ***** Variables *****/
unsigned static int const WIDTH  = 400;
unsigned static int const HEIGHT = 400;
sf::Uint8 *pixels = new sf::Uint8[WIDTH * HEIGHT * 4]; //RGBA

/* ***** Functions *****/
void setPixel( unsigned int x, unsigned int y, float value ) {
    pixels[4*(y * WIDTH + x)]     = value * 255;
    pixels[4*(y * WIDTH + x) + 1] = value * 255;
    pixels[4*(y * WIDTH + x) + 2] = value * 255;
    pixels[4*(y * WIDTH + x) + 3] = value * 255;
}

void generateNoise( void ) {
    SimplexNoise noiseGenerator;
    for ( std::size_t y=0; y<HEIGHT; ++y ) {
        for ( std::size_t x=0; x<WIDTH; ++x ) {
            float xPos = float( x ) / float( WIDTH )  - 0.5f;
            float yPos = float( y ) / float( HEIGHT ) - 0.5f;
            float octaves = 5;

            float value = noiseGenerator.unsignedOctave( octaves, xPos, yPos );
            setPixel( x, y, value );
        }
    }
}

/* ***** Main *****/
int main() {
    srand( time(0) );
    sf::RenderWindow window( sf::VideoMode(WIDTH, HEIGHT), "Simplex Noise 2D visualisation" );

    sf::Texture texture;
    texture.create( WIDTH, HEIGHT );

    sf::Sprite sprite;
    sprite.setTexture( texture );

    generateNoise();
    texture.update( pixels );

    while ( window.isOpen() ) {
        sf::Event event;
        while ( window.pollEvent(event) ) {
            if ( event.type == sf::Event::Closed ) {
                window.close();
            }
        }

        window.draw( sprite );
        window.display();
    }

    delete pixels;
	
    return EXIT_SUCCESS;
}