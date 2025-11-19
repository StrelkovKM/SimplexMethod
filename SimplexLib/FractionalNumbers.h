#pragma once
#include <iostream>

class frac
{
protected:
	size_t numerator;
	size_t denominator;
	int sign;
public:
	frac();
	frac(int numerator_, int denominator_);
	frac(int integer_number);
	frac(const frac& other);
	frac operator+(const frac& other);
	frac operator-(const frac& other);
	frac operator*(const frac& other);
	frac operator/(const frac& other);
	frac& operator+=(const frac& other);
	frac& operator-=(const frac& other);
	frac& operator*=(const frac& other);
	frac& operator/=(const frac& other);
	frac& operator=(const frac& other);
	bool operator==(const frac& other);
	bool operator!=(const frac& other);
	bool operator==(int other);
	bool operator!=(int other);
	bool operator<(const frac& other);
	bool operator<(int other);
	bool operator>(const frac& other);
	bool operator>(int other);
	friend std::ostream& operator<<(std::ostream& out, const frac& other);
};

int GCD(int number1, int number2);
