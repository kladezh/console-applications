#pragma once

#include <iostream>
#include <windows.h>

#define REGULAR_CONSOLE_ATTRIBUTE static_cast<WORD>(15)

class TextAttr {
private:
	WORD value;

public:
	explicit TextAttr(WORD attributes) : value(attributes)
	{
	}

	friend std::ostream& operator<<(std::ostream& out, TextAttr attr) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), attr.value);
		return out;
	}
};