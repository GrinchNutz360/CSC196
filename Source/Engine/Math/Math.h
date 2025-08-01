#pragma once
#include <SDL3/SDL.h>
#include <algorithm>
#include <cmath>
namespace viper {
	namespace math {
		constexpr float pi = 3.14159265358979323846f;
		constexpr float twoPi = pi * 2.0f;
		constexpr float halfPi = pi / 2.0f;

		/// <summary>
		/// Converts an angle from radians to degrees.
		/// </summary>
		/// <param name="rad">The angle in radians to convert.</param>
		/// <returns>The equivalent angle in degrees.</returns>
		constexpr float radToDeg(float rad) { return rad * (180 / pi); }
		/// <summary>
		/// Converts an angle from degrees to radians.
		/// </summary>
		/// <param name="deg">The angle in degrees to convert.</param>
		/// <returns>The angle in radians.</returns>
		constexpr float degToRad(float deg) { return deg * (pi / 180); }


		/// <summary>
		/// Wraps an integer value within a specified range [min, max), cycling around if the value is outside the range.
		/// </summary>
		/// <param name="value">The integer value to wrap.</param>
		/// <param name="min">The inclusive lower bound of the range.</param>
		/// <param name="max">The exclusive upper bound of the range.</param>
		/// <returns>The wrapped integer value within the range [min, max).</returns>
		constexpr int wrap(int value, int min, int max) {
			int range = max - min;				
			int result = (value - min) % range;
			if (result < 0) result += range;

			return min + result;
		}

		/// <summary>
		/// Wraps a floating-point value into the range [min, max) using modular arithmetic.
		/// </summary>
		/// <param name="value">The value to wrap within the specified range.</param>
		/// <param name="min">The lower bound of the range (inclusive).</param>
		/// <param name="max">The upper bound of the range (exclusive).</param>
		/// <returns>The wrapped value, guaranteed to be within [min, max).</returns>
		inline float wrap(float value, float min, float max) {
			float range = max - min;
			float result = std::fmodf(value - min, range);
			if (result < 0) result += range;

			return min + result;
		}

		template <typename T>
		inline T sign(T v) {
			return (v < 0) ? (T) - 1 : (v > 0) ? (T)1 : (T)0;
		}

		using std::min;
		using std::max;
		/*using std::clamp;*/
		using std::sqrt;
		using std::sqrtf;
		using std::acos;
		using std::acosf;
		using std::sin;
		using std::sinf;
		using std::cos;
		using std::cosf;
		using std::atan2;
		using std::atan2f;
	}
}
