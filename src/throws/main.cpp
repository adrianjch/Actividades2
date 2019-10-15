#include <iostream>
#include <exception>


float division(float a, float b) {
	if (b == 0)
		throw std::exception("Division by zero condition!");
	return a / b;
}


int main() {
	try {
		float result = division(10.f, 3.f);
	}
	catch (std::exception e) {
		std::cout << e.what << std::endl;
	}

	return 0;
}