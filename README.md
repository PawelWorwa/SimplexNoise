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
```cpp
void  randomizeSeed ( void );
```
Generate random seed (by shuffling perutation table) to prevent same output each time.


```cpp
void  setFrequency  ( float frequency ) { this->frequency = frequency; };
```
Frequency determines "zoom" level for generated pattern. Best results are achieved, when parameter is within range **1.0f – 16.0f** If omitted, default value will be used (**1.0f**). Differences between various frequency values (1, 2 and 4) are presented below:

![Frequency](http://i.imgur.com/4PWOJUx.png)


```cpp
void  setOctaves    ( int octaves ) { this->octaves = octaves; };
```
Octaves are sum of noises generated on different frequencies. Best results are achieved, when parameter is within range **1 – 6**. If omitted, default value will be used (**1**). Differences between various octaves (1, 2 and 3) are presented below:

![Octaves](http://i.imgur.com/LVkToA0.png)


```cpp
void  setPersistence( float persistence ) { this->persistence = persistence; };
```
I admit that it's ‘hard’ for me to explain in short word’s what exactly is persistence. Making use of explanation I’ve found [here](http://libnoise.sourceforge.net/glossary/#persistence).
>“**Persistence**
A multiplier that determines how quickly the amplitudes diminish for each successive octave in a Perlin-noise function.“

Best results are achieved, when parameter is within range **0.0f – 1.0f**. If omitted, default value will be used (**0.5f**).  Differences between various persistence values (0.4f, 0.5f and 0.6f) are presented below:

![Persistence](http://i.imgur.com/cS3XzoA.png)


```cpp
float signedOctave  ( float xPos, float yPos );
```
Function returns cumulative noise value from range -1 to 1. Total number of noise functions that are added together are described by ‘Octaves’ parameter.


```cpp
float unsignedOctave( float xPos, float yPos );
```
Same as `signedOctave` with difference that it returns value from range 0 to 1.

## Output
How does it looks in practice?. It’s being well illustrated by sample pictures below (yes… it’s this library output):

**Greyscale**

![GreyScale](http://i.imgur.com/PrclqgJ.png)

**Terrain maps**

![Terrain](http://i.imgur.com/8gqNnrQ.png)

## Usage
Basic usage 
```cpp
SimplexNoise noiseGenerator;

float xValue = 100.0f;
float yValue = 100.0f;
float value = noiseGenerator.unsignedOctave( xValue, yValue );
```

..and that’s it.

## License
This project is licensed under the [MIT License](https://opensource.org/licenses/MIT) - see the **LICENSE** file for details