# Simplex Noise for 2D space
## Introduction
>“Simplex noise is a method for constructing an n-dimensional noise function comparable to Perlin noise ("classic" noise) but with fewer directional artefacts and, in higher dimensions, a lower computational overhead. Ken Perlin designed the algorithm in 2001 to address the limitations of his classic noise function, especially in higher dimensions.“ Description taken from [Wikipedia](https://en.wikipedia.org/wiki/Simplex_noise).

## About this library
Aside from couple of changes and modifications (or to be more precisely, extensions), this library is direct port of Java algorithm presented by Stefan Gustavson and optimised by Peter Eastman.

Original algorithm site:
- Code:	 http://webstaff.itn.liu.se/~stegu/simplexnoise/SimplexNoise.java
- Description:	http://staffwww.itn.liu.se/~stegu/simplexnoise/simplexnoise.pdf

For octaves (Fractures) used algorithm from [this site](http://flafla2.github.io/2014/08/09/perlinnoise.html).

For the sake of simplicity (personally, I like to include just one pair of header and class file), cpp class include two embedded classes. I know they could (and should) be optimised and keep as separate beings but like I said, it’s all for the sake of usage simplicity.

## Visualisation
For testing and visualisation purposes , [SFML](https://www.sfml-dev.org/) (Simple and Fast Multimedia Library) was used. 

## Function description
To generate a noise, one of two functions are used: noise or octave. 
```cpp
float noise ( float xPos, float yPos );
```
Function returns noise value from range -1 to 1;
```cpp
float octave( int octaves, float xPos, float yPos );
```
Function returns cumulative noise value from range -1 to 1. Total number of noise functions that are added together are described by ‘Octaves’ parameter.
```cpp
float unsignedNoise ( float xPos, float yPos );
```
Same as noise function with difference, that it returns value from 0 to 1.
```cpp
float unsignedOctave( int octaves, float xPos, float yPos );
```
Same as octave function with difference, that it returns value from 0 to 1.
```cpp
void  randomizeSeed ( void );
```
Set random seed to prevent same result each time.

## Output
How does it looks in practice?. It’s being well illustrated by picture below (yes… it’s this library output):
![Octaves](http://i.imgur.com/WyspYaV.png)

To put it simply, the higher octaves (more noise functions added together) than more sophisticated output. 

## Usage
Basic usage 
```cpp
SimplexNoise noiseGenerator;

float xValue = 100.0f;
float yValue = 100.0f;
float value = noiseGenerator.noise( xValue, yValue );
```

..and that’s it.

## License
This project is licensed under the [MIT License](https://opensource.org/licenses/MIT) - see the **LICENSE** file for details