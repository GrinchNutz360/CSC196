#pragma once
#include <algorithm>
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
		constexpr float radToDeg(float rad) { return rad = (180 / pi); }
		/// <summary>
		/// Converts an angle from degrees to radians.
		/// </summary>
		/// <param name="deg">The angle in degrees to convert.</param>
		/// <returns>The angle in radians.</returns>
		constexpr float degToRad(float deg) { return deg = (pi / 180); }

		using std::min;
		using std::max;
		using std::clamp;
	}
}
