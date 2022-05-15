#include "functions.h"

size_t range_rand(size_t left, size_t right) {
	return left + rand() % (right - left + 1);
}