# Simplex Noise implementation for 2D space
## Introduction
>“Simplex noise is a method for constructing an n-dimensional noise function comparable to Perlin noise ("classic" noise) but with fewer directional artefacts and, in higher dimensions, a lower computational overhead. Ken Perlin designed the algorithm in 2001 to address the limitations of his classic noise function, especially in higher dimensions.“ Description taken from [Wikipedia](https://en.wikipedia.org/wiki/Simplex_noise).

## About this library
Aside from couple of changes and modifications (or to be more precisely, extensions), this library is direct port of Java algorithm presented by **Stefan Gustavson** and optimised by **Peter Eastman**.

Original algorithm site:
- Code:	 http://webstaff.itn.liu.se/~stegu/simplexnoise/SimplexNoise.java
- Description:	http://staffwww.itn.liu.se/~stegu/simplexnoise/simplexnoise.pdf

## Functions description
```cpp
void randomizeSeed();
```
Generate random seed (by shuffling permutation table) to prevent same output each time.

```cpp
void setSeed(const unsigned int &seedNumber);
```
Set custom seed to produce the same, expected output each time.

```cpp
double signedRawNoise(const double &xPos, const double &yPos);
```
Get raw signed noise value.

```cpp
double unsignedRawNoise(const double &xPos, const double &yPos);
```
Get raw unsigned noise value.

```cpp
double signedFBM(const double &xPos, const double &yPos, const unsigned int &octaves, const double &lacunarity, const double &gain);
```
FBM stands for Fractal Brownian Motion - get signed fractal value.
More about fractals can be seen [here](https://www.scratchapixel.com/lessons/procedural-generation-virtual-worlds/procedural-patterns-noise-part-1/simple-pattern-examples).

```cpp
double unsignedFBM(const double &xPos, const double &yPos, const unsigned int &octaves, const double &lacunarity, const double &gain);
```
The same as above but returns unsgined fractal value.

## Raw noise and Fractal Brownian Motion
Fractional Brownian Motion is the summation of successive octaves of noise, each with higher frequency and lower amplitude.
Saying it simply, its an output of couple of different noises combined.

Results can be seen below (with raw noise output visualisation to the left). As one can see, FBM result in more sophisticated output:

![Imgur](https://i.imgur.com/G2Y1qdv.png)

Fractal Brownian Motion is determined by: 
* **xPos**       - x value for noise
* **yPos**       - y value for noise
* **octaves**    - how many noise layers are used (number of octaves determines how detailed the output will be).
Differences between various octaves (1, 2 and 3) are presented below:

![Octaves](http://i.imgur.com/LVkToA0.png)

* **lacunarity** - is what makes the frequency grow as each octave the frequency is multiplied by the lacunarity
Differences between various lacunarity values (1.0, 1.5 and 2.1042) are presented below:

![Lacunarity](https://i.imgur.com/Cw9P75z.png)

* **gain**       - also called persistence, is what makes the amplitude shrink (or not shrink). Each octave the amplitude is multiplied by the gain
Differences between various persistence values (0.4, 0.5 and 0.6) are presented below:

![Persistence](http://i.imgur.com/cS3XzoA.png)

* **frequency**  - additional parameter applied directly to xPos and yPos. It determines "zoom" level for generated pattern. 
Differences between various frequency values (1, 2 and 4) are presented below:

![Frequency](http://i.imgur.com/4PWOJUx.png)

## Output
How does it looks in practice?. It’s being well illustrated by below example (for the sake of simplicity, result is in greyscale):

![GreyScale](http://i.imgur.com/PrclqgJ.png)

## Usage 
Example usage
```cpp
    const unsigned int WIDTH = 800;
    const unsigned int HEIGHT = 600;
    
    SimplexNoise noise;
    
    for ( std::size_t y = 0; y < HEIGHT; ++y ) {
        for ( std::size_t x = 0; x < WIDTH; ++x ) {
            double xPos = double( x ) / double( WIDTH ) - 0.5;
            double yPos = double( y ) / double( HEIGHT ) - 0.5;
    
            double noiseValue = noise.signedRawNoise( xPos, yPos );
            // do whatever you want with noiseValue here
        }
    }
```

## Examples
[Random world](./examples/README.md) playground visualised using [SFML](https://www.sfml-dev.org/) library.

## Additional articles 
* Octaves (Fractal) algorithm   : http://flafla2.github.io/2014/08/09/perlinnoise.html
* Fractional Brownian Motion    : https://www.scratchapixel.com/lessons/procedural-generation-virtual-worlds/procedural-patterns-noise-part-1/simple-pattern-examples
* Good tutorial how to generate terrain from noise (at least in my opinion): https://www.redblobgames.com/maps/terrain-from-noise/

## License
This project is licensed under the [MIT License](https://opensource.org/licenses/MIT) - see the **LICENSE** file for more details