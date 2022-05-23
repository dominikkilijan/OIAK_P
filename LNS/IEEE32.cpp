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
//=======================================================================================================================================================================
// operacje matematyczne
//=======================================================================================================================================================================

//================================
// mnozenie
//================================
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
    float mant2 = ((float)num2.mantissa / 8388608) + 1; // w artykule to jest (1+ f)

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
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
IEEE32 IEEE32::mulLNS(IEEE32 num1, IEEE32 num2)
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

    float k1 = log2(mant1); // tutaj mozna pokombinowac jesli zwykla funkcja log2 bedzie zbyt wolna
    float k2 = log2(mant2);

    float mant3 = powf(2, (k1 + k2));
    std::cout << "podzielone mantysy: " << mant3 << "\n";

    if (mant3 > 2)
    {
        mant3 = mant3 / 2;
        result.exponent++;
        std::cout << "pomnozone mantysy: " << mant3 << "\n";
    }

    result.mantissa = (int)((mant3 - 1) * 8388608); // powrot do postaci int np 1110010...0

    return result;
}
//======================================================================================================================================================================================

//================================
// dzielenie
//================================
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
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
IEEE32 IEEE32::divLNS(IEEE32 num1, IEEE32 num2)
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

    float k1 = log2(mant1); // tutaj mozna pokombinowac jesli zwykla funkcja log2 bedzie zbyt wolna
    float k2 = log2(mant2);

    float mant3 = powf(2, (k1 - k2));
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
//======================================================================================================================================================================================

//================================
// pierwiastek
//================================
void IEEE32::sr()
{
    if (this->sign == 0)
    {
        // wykladnik
        this->exponent = (this->exponent - 127)/2 + 127;
        std::cout << "Wykladnik do pierwiastka: " << this->exponent << "\n";

        // mantysa
        float mant1 = ((float)this->mantissa / 8388608) + 1; // dzielimy przez 2^23 zeby bylo mniejsze niz 1 i inkrementujemy np 110...0 => 0.11 + 1 = 1.11
        std::cout << "Mantysa do pierwiastka przed pierwiastkiem: " << mant1 << "\n";
        mant1 = sqrt(mant1);
        std::cout << "Mantysa po pierwiastku: " << mant1 << "\n";

        if (mant1 > 2)
        {
            mant1 = mant1 / 2;
            this->exponent++;
            std::cout << "Mantysa po pierwiastku: " << mant1 << "\n";
        }
        if (mant1 < 1)
        {
            mant1 = mant1 * 2;
            this->exponent--;
            std::cout << "Mantysa po pierwiastku: " << mant1 << "\n";
        }

        this->mantissa = (int)((mant1 - 1) * 8388608); // powrot do postaci int np 1110010...0
    }
    else std::cout << "Ujemna liczba" << "\n";

}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
void IEEE32::srLNS()
{
    //code
}
//======================================================================================================================================================================================

//================================
// odwrotnosc pierwiastka
//================================
void IEEE32::isr()
{
    if (this->sign == 0)
    {
        // wykladnik
        int exp = (int)this->exponent;
        std::cout << "Exp 1: " << exp << "\n";
        exp = ((exp - 127) / -2 + 127);
        std::cout << "Exp 1: " << exp << "\n";
        this->exponent = exp;
        std::cout << "Wykladnik do pierwiastka: " << this->exponent << "\n";

        // mantysa
        float mant1 = ((float)this->mantissa / 8388608) + 1; // dzielimy przez 2^23 zeby bylo mniejsze niz 1 i inkrementujemy np 110...0 => 0.11 + 1 = 1.11
        std::cout << "Mantysa do pierwiastka przed pierwiastkiem: " << mant1 << "\n";
        mant1 = powf((sqrt(mant1)), -1);
        std::cout << "Mantysa po pierwiastku: " << mant1 << "\n";

        if (mant1 > 2)
        {
            mant1 = mant1 / 2;
            this->exponent++;
            std::cout << "Mantysa po pierwiastku: " << mant1 << "\n";
        }
        if (mant1 < 1)
        {
            mant1 = mant1 * 2;
            this->exponent--;
            std::cout << "Mantysa po pierwiastku: " << mant1 << "\n";
        }

        this->mantissa = (int)((mant1 - 1) * 8388608); // powrot do postaci int np 1110010...0
    }
    else std::cout << "Ujemna liczba" << "\n";
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
void IEEE32::isrLNS()
{
    //code
}