#pragma once
#include <stdlib.h>
namespace viper {
	namespace random {

		/// <summary>
		/// Generates a random integer value
		/// </summary>
		/// <returns></returns>
		inline int getRandom() { return rand(); }


		/// <summary>
		/// Generates a random integer in the range [0, max).
		/// </summary>
		/// <param name="max">The upper bound (exclusive) for the random integer.</param>
		/// <returns>A random integer greater than or equal to 0 and less than max.</returns>
		inline int getRandomInt(int max) { return rand() % max; }
		
		/// <summary>
		/// Generates a random integer within a specified inclusive range.
		/// </summary>
		/// <param name="min">The lower bound of the range (inclusive).</param>
		/// <param name="max">The upper bound of the range (inclusive).</param>
		/// <returns>A random integer between min and max, inclusive.</returns>
		inline int getRandomInt(int min, int max) { return min + getRandomInt(max - min + 1); }
	
		/// <summary>
		/// Generates a random floating-point number between 0.0 and 1.0.
		/// </summary>
		/// <returns>A random float value in the range [0.0, 1.0].</returns>
		inline float getRandomFloat() { return rand() / (float)RAND_MAX; }
	}
}