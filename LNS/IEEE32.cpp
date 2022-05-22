#include "IEEE32.h"
#include <iostream>
#include <bitset>

void IEEE32::printNumber()
    {
        std::cout << "Wartosc liczby: " << this->fValue << "\n";
        std::cout << "IEEE32: " << this->sign << "   ";
        std::bitset<8> x(this->exponent);
        std::cout << x << "   ";
        std::bitset<23> y(this->mantissa);
        std::cout << y << "\n";
    }
//===================================================================
// operacje matematyczne
//===================================================================

// mnozenie
IEEE32 IEEE32::mul(IEEE32 num1, IEEE32 num2)
{
    IEEE32 result(0);
    //code
    return result;
}

IEEE32 IEEE32::mulLNS(IEEE32 num1, IEEE32 num2)
{
    IEEE32 result(0);
    //code
    return result;
}
//-------------------------------------------------------------------
// dzielenie
IEEE32 IEEE32::div(IEEE32 num1, IEEE32 num2)
{
    IEEE32 result(0);
    //code
    return result;
}

IEEE32 IEEE32::divLNS(IEEE32 num1, IEEE32 num2)
{
    IEEE32 result(0);
    //code
    return result;
}
//-------------------------------------------------------------------
// pierwiastek
void IEEE32::sr()
{
    //code
}

void IEEE32::srLNS()
{
    //code
}
//-------------------------------------------------------------------
// odwrotnosc pierwiastka
void IEEE32::isr()
{
    //code
}

void IEEE32::isrLNS()
{
    //code
}