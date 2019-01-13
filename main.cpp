#include <SFML/Graphics.hpp>
#include "SimplexNoise.hpp"

#include <cstdlib>
#include <ctime>
#include <memory>

/* ***** Simplex noise visualisation example *****/
class ExampleNoise {
    public:
        explicit ExampleNoise( unsigned int width, unsigned int height ) : height( height ), width( width ) {
            noiseTexture.create( width, height );
            pixels = std::unique_ptr< sf::Uint8[] >( new sf::Uint8[width * height * 4] );
        };

        void drawNoise( sf::RenderWindow &window ) {
            sf::Sprite noiseSprite;
            noiseSprite.setTexture( noiseTexture );
            window.draw( noiseSprite );
        };

        void generateNoise() {
            SimplexNoise noiseGenerator;
//            noiseGenerator.randomizeSeed();

            for ( std::size_t y = 0; y < height; ++y ) {
                for ( std::size_t x = 0; x < width; ++x ) {
                    double xPos = double( x ) / double( width ) - 0.5;
                    double yPos = double( y ) / double( height ) - 0.5;

                    double elevation = std::pow(
                            noiseGenerator.unsignedFBM( frequency * xPos, frequency * yPos, octaves, lacunarity, gain ),
                            redistribution );
                    setPixel( x, y, elevation );
                }
            }

            noiseTexture.update( pixels.get());
        };

    private:
        unsigned int height;
        unsigned int width;
        sf::Texture noiseTexture;
        std::unique_ptr< sf::Uint8[] > pixels;

        /* Values for FBM that produce  nice" output */
        const unsigned int octaves = 7;
        const double lacunarity = 2.1042;
        const double gain = 0.575;
        const double redistribution = 1.8;
        const double frequency = 1.5;

        void setPixel( unsigned int x, unsigned int y, double value ) {
            auto rgba = static_cast<sf::Uint8>(value * 255);
            sf::Color color( rgba, rgba, rgba, rgba );

            pixels[4 * ( y * width + x )]     = color.r;
            pixels[4 * ( y * width + x ) + 1] = color.g;
            pixels[4 * ( y * width + x ) + 2] = color.b;
            pixels[4 * ( y * width + x ) + 3] = color.a;
        };
};

/* ***** Main *****/
int main() {
    const unsigned int width = 800;
    const unsigned int height = 600;

    ExampleNoise noise( width, height );
    noise.generateNoise();

    sf::RenderWindow window( sf::VideoMode( width, height ), "Simplex Noise 2D visualisation" );
    while ( window.isOpen()) {
        sf::Event event;
        while ( window.pollEvent( event )) {
            if ( event.type == sf::Event::Closed ) {
                window.close();
            }
        }

        window.clear( sf::Color::Black );
        noise.drawNoise( window );
        window.display();
    }

    return EXIT_SUCCESS;
}
