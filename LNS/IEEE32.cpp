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

    // znak
    if (num1.sign != num2.sign) result.sign = 1;
    else result.sign = 0;

    //wykladnik
    result.exponent = (num1.exponent - 127) + num2.exponent;

    // mantysa
    float mant1 = ((float)num1.mantissa / 8388608) + 1; // dzielimy przez 2^23 zeby bylo mniejsze niz 1 i inkrementujemy np 110...0 => 0.11 + 1 = 1.11
    float mant2 = ((float)num2.mantissa / 8388608) + 1;

    std::cout << "mantysa liczby 1 po podzieleniu: " << mant1 << "\n";
    std::cout << "mantysa liczby 2 po podzieleniu: " << mant2 << "\n";

    float mant3 = mant1 * mant2;
    std::cout << "pomnozone mantysy: " << mant3 << "\n";

    if (mant3 > 2)
    {
        mant3 = mant3 / 2;
        result.exponent++;
        std::cout << "pomnozone mantysy: " << mant3 << "\n";
    }

    result.mantissa = (int)((mant3 - 1) * 8388608); // powrot do postaci int np 1110010...0
    
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

    // znak
    if (num1.sign != num2.sign) result.sign = 1;
    else result.sign = 0;

    //wykladnik
    result.exponent = (num1.exponent + 127) - num2.exponent;

    // mantysa
    float mant1 = ((float)num1.mantissa / 8388608) + 1; // dzielimy przez 2^23 zeby bylo mniejsze niz 1 i inkrementujemy np 110...0 => 0.11 + 1 = 1.11
    float mant2 = ((float)num2.mantissa / 8388608) + 1;

    std::cout << "mantysa liczby 1 po podzieleniu: " << mant1 << "\n";
    std::cout << "mantysa liczby 2 po podzieleniu: " << mant2 << "\n";

    float mant3 = mant1 / mant2;
    std::cout << "podzielone mantysy: " << mant3 << "\n";

    if (mant3 < 1)
    {
        mant3 = mant3 * 2;
        result.exponent--;
        std::cout << "podzielone mantysy: " << mant3 << "\n";
    }

    result.mantissa = (int)((mant3 - 1) * 8388608); // powrot do postaci int np 1110010...0

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