#pragma once
#include "../Math/Vector2.h"
#include "../Math/Math.h"
#include <stdlib.h>
#include <random>
#include <memory>
namespace viper {
    namespace random {

        /// <summary>
        /// Returns a reference to a static Mersenne Twister random number generator.
        /// </summary>
        /// <returns>A reference to a static std::mt19937 random number generator instance.</returns>
        inline std::mt19937& generator() {
            static std::random_device rd;
            static std::mt19937 gen(rd());
            return gen;
        }

        /// <summary>
        /// Sets the seed value for the random number generator.
        /// </summary>
        /// <param name="value">The seed value to initialize the random number generator.</param>
        inline void seed(unsigned int value) {
            generator().seed(value);
        }

        /// <summary>
        /// Generates a random integer within the specified range [min, max].
        /// </summary>
        /// <param name="min">The lower bound of the range (inclusive).</param>
        /// <param name="max">The upper bound of the range (inclusive).</param>
        /// <returns>A random integer between min and max, inclusive.</returns>
        inline int getInt(int min, int max) {
            std::uniform_int_distribution<> dist(min, max);
            return dist(generator());
        }

        /// <summary>
        /// Returns an integer in the range [0, max - 1] by calling getInt with the specified bounds.
        /// </summary>
        /// <param name="max">The exclusive upper bound for the random integer.</param>
        /// <returns>An integer between 0 and max - 1, inclusive of 0 and exclusive of max.</returns>
        inline int getInt(int max) {
            return getInt(0, max - 1);
        }

        /// <summary>
        /// Generates a random integer using a uniform distribution.
        /// </summary>
        /// <returns>A randomly generated integer value.</returns>
        inline int getInt() {
            static std::uniform_int_distribution<> dist;
            return dist(generator());
        }

        /// <summary>
        /// Generates a random real number within the specified range [min, max).
        /// </summary>
        /// <typeparam name="T">The type of the real number to generate. Defaults to float.</typeparam>
        /// <param name="min">The lower bound of the range (inclusive).</param>
        /// <param name="max">The upper bound of the range (exclusive).</param>
        /// <returns>A random real number of type T in the range [min, max).</returns>
        template <typename T = float>
        inline T getReal(T min, T max) {
            std::uniform_real_distribution<T> dist(min, max);
            return dist(generator());
        }

        /// <summary>
        /// Returns a random real number in the range [0, max).
        /// </summary>
        /// <typeparam name="T">The type of the real number to generate. Defaults to float.</typeparam>
        /// <param name="max">The exclusive upper bound for the generated random number.</param>
        /// <returns>A random real number of type T greater than or equal to 0 and less than max.</returns>
        template <typename T = float>
        inline T getReal(T max) {
            return getReal(static_cast<T>(0), static_cast<T>(max));
        }

        /// <summary>
        /// Generates a random real number in the range [0, 1).
        /// </summary>
        /// <typeparam name="T">The floating-point type of the generated number. Defaults to float.</typeparam>
        /// <returns>A random real number of type T in the range [0, 1).</returns>
        template <typename T = float>
        inline T getReal() {
            static std::uniform_real_distribution<T> dist(static_cast<T>(0), static_cast<T>(1));
            return dist(generator());
        }
        
        /// <summary>
        /// Generates a random boolean value with equal probability for true or false.
        /// </summary>
        /// <returns>A boolean value: true or false, each with a probability of 0.5.</returns>
        inline bool getBool() {
            static std::bernoulli_distribution dist(0.5);
            return dist(generator());
        }

        inline vec2 onUnitCircle() {
            float radians = getReal(math::twoPi);
            return vec2{ math::cosf(radians), math::sinf(radians) };
        }
    }
}