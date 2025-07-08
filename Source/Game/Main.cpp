#include "Math/Math.h"
#include "Core/Random.h"
#include <iostream>
#define NAME "Tristin"
int main() {

	//const float deg = viper::radToDeg(viper::pi);
	viper::math::min(5, 3);

	std::cout << NAME;
	std::cout << "Hello, World!\n";
	std::cout << viper::math::pi << std::endl;

	for (int i = 0; i < 10; i++) {
		std::cout << viper::random::getRandomFloat() << std::endl;
	}
}