#include "IEEE16.h"
#include <iostream>
#include <bitset>

void IEEE16::printNumber()
{
    std::cout << "Wartosc liczby: " << this->fValue << "\n";
    std::cout << "IEEE16: " << this->sign << "   ";
    std::bitset<5> x(this->exponent);
    std::cout << x << "   ";
    std::bitset<10> y(this->mantissa);
    std::cout << y << "\n";
}