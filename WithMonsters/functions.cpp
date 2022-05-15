#include "functions.h"

size_t range_rand(size_t left, size_t right) {
	return left + rand() % (right - left + 1);
}

bool take_chance(size_t bad, size_t good) {
	size_t* arr = new size_t[bad + good];
	for (size_t i = 0; i < bad + good; i++) {
		if (i < bad) {
			arr[i] = 0;
		}
		else {
			arr[i] = 1;
		}
	}

	bool chance = static_cast<bool>(arr[range_rand(0, static_cast<int>(bad + good))]);

	delete[] arr;
	return chance;
}
