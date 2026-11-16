#ifndef MATHLIB_PERLINNOISE_H
#define MATHLIB_PERLINNOISE_H

#include <vector>

namespace MathLib
{

class PerlinNoise
{
        // The permutation vector
        std::vector<unsigned int> p;
public:
        // Initialize with the reference values for the permutation vector
        PerlinNoise();
        // Generate a new permutation vector based on the value of seed
        PerlinNoise(unsigned int seed);
        // Get a noise value, for 2D images z can have any value
        double noise(double x, double y, double z);
        double octaveNoise(double x, double y, double z, int octaves, double persistence);
private:
        double fade(double t);
        double lerp(double t, double a, double b);
        double grad(unsigned int hash, double x, double y, double z);
};

} //namespace MathLib

#endif //MATHLIB_PERLINNOISE_H
