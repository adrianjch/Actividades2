#include <iostream>


void division(float a, float b) {
	if (b == 0)
		throw "Division by zero condition!";
	else if (b != 0)
		throw a / b;
}

int main() {
	float result;
	try {
		division(10.f, 3.f);
	}
	catch (const char* msg) {
		std::cout << msg << std::endl;
	}
	catch (float msg) {
		std::cout << msg << std::endl;
		result = msg;
	}

	return 0;
}