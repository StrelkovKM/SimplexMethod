#include "FractionalNumbers.h"

frac::frac()
{
    numerator = 0;
    denominator = 1;
    sign = 1;
}

frac::frac(int numerator_, int denominator_)
{
    if (denominator_ == 0)
        throw "division_by_zero";

    if (numerator_ == 0) {
        numerator = 0;
        denominator = 1;
        sign = 1;
        return;
    }

    if ((numerator_ > 0 && denominator_ > 0) || (numerator_ < 0 && denominator_ < 0))
        sign = 1;
    else
        sign = -1;

    int abs_num = std::abs(numerator_);
    int abs_den = std::abs(denominator_);

    int gcd = GCD(abs_num, abs_den);

    numerator = abs_num / gcd;
    denominator = abs_den / gcd;
}

frac::frac(int integer_number)
{
    if (integer_number >= 0)
        sign = 1;
    else
        sign = -1;
    numerator = std::abs(integer_number);
    denominator = 1;
}

frac::frac(const frac& other)
{
    numerator = other.numerator;
    denominator = other.denominator;
    sign = other.sign;
}

frac frac::operator+(const frac& other)
{
    int new_num = numerator * other.denominator * sign + other.numerator * denominator * other.sign;
    int new_den = denominator * other.denominator;
    return frac(new_num, new_den);
}

frac frac::operator-(const frac& other)
{
    int new_num = numerator * other.denominator * sign - other.numerator * denominator * other.sign;
    int new_den = denominator * other.denominator;
    return frac(new_num, new_den);
}

frac frac::operator*(const frac& other)
{
    int new_num = numerator * other.numerator;
    int new_den = denominator * other.denominator;
    int new_sign = sign * other.sign;
    return frac(new_sign * new_num, new_den);
}

frac frac::operator/(const frac& other)
{
    if (other.numerator == 0)
        throw "division_by_zero";

    int new_num = numerator * other.denominator;
    int new_den = denominator * other.numerator;
    int new_sign = sign * other.sign;
    return frac(new_sign * new_num, new_den);
}

frac& frac::operator+=(const frac& other)
{
    *this = *this + other;
    return *this;
}

frac& frac::operator-=(const frac& other)
{
    *this = *this - other;
    return *this;
}

frac& frac::operator*=(const frac& other)
{
    *this = *this * other;
    return *this;
}

frac& frac::operator/=(const frac& other)
{
    *this = *this / other;
    return *this;
}

frac& frac::operator=(const frac& other)
{
    numerator = other.numerator;
    denominator = other.denominator;
    sign = other.sign;
    return *this;
}

bool frac::operator==(const frac& other)
{
    frac diff = *this - other;
    return diff.numerator == 0;
}

bool frac::operator!=(const frac& other)
{
    return !(*this == other);
}

bool frac::operator==(int other)
{
    return *this == frac(other);
}

bool frac::operator!=(int other)
{
    return !(*this == other);
}

bool frac::operator<(const frac& other)
{
    frac diff = *this - other;
    return diff.sign == -1;
}

bool frac::operator<(int other)
{
    return *this < frac(other);
}

bool frac::operator>(const frac& other)
{
    frac diff = *this - other;
    return diff.sign == 1 && diff.numerator != 0;
}

bool frac::operator>(int other)
{
    return *this > frac(other);
}

std::ostream& operator<<(std::ostream& out, const frac& other)
{
    if (other.sign == -1 && other.numerator != 0)
        out << "-";
    if (other.denominator == 1)
        out << other.numerator;
    else
        out << other.numerator << "/" << other.denominator;
    return out;
}

int GCD(int number1, int number2)
{
    number1 = std::abs(number1);
    number2 = std::abs(number2);

    if (number1 == 0 && number2 == 0)
        return 1;
    if (number1 == 0) return number2;
    if (number2 == 0) return number1;

    while (number2 != 0)
    {
        int temp = number2;
        number2 = number1 % number2;
        number1 = temp;
    }
    return number1;
}