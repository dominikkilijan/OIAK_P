#include "IEEE16.h"
#include "IEEE16.h"
#include <iostream>
#include <bitset>
#include <iomanip>
#include <windows.h>



void IEEE16::printNumber()
{
    IEEE32 printNum;
    printNum.sign = this->sign;
    printNum.exponent = this->exponent + 112;       // uwzglednienie biasu float
    printNum.mantissa = this->mantissa * 8192;      // przesuniecie 10 bitow z half-precision na najstarsze bity mantysy single-precision
    std::cout << "Wartosc liczby: " << std::fixed << std::setprecision(5) << printNum.fValue << "\n";
    std::cout << "IEEE16: " << this->sign << "   ";
    std::bitset<5> x(this->exponent);
    std::cout << x << "   ";
    std::bitset<10> y(this->mantissa);
    std::cout << y << "\n";
}
//=======================================================================================================================================================================
// operacje matematyczne
//=======================================================================================================================================================================

//================================
// mnozenie
//================================
IEEE16 IEEE16::mul(IEEE16 num1, IEEE16 num2)
{
    IEEE16 result(0);
    // znak
    if (num1.sign != num2.sign) result.sign = 1;
    else result.sign = 0;

    //wykladnik
    result.exponent = (num1.exponent - 15) + num2.exponent;

    // mantysa
    float mant1 = ((float)num1.mantissa / 1024) + 1; // dzielimy przez 2^10 zeby bylo mniejsze niz 1 i inkrementujemy np 110...0 => 0.11 + 1 = 1.11
    float mant2 = ((float)num2.mantissa / 1024) + 1; // w artykule to jest (1+f)

    float mant3 = mant1 * mant2;

    if (mant3 > 2)
    {
        mant3 = mant3 / 2;
        result.exponent++;
        std::cout << "pomnozone mantysy: " << mant3 << "\n";
    }
    //else std::cout << "pomnozone mantysy: " << mant3 << "\n";

    mant3 = ((mant3 - 1) * 1024);
    result.mantissa = (int)ceil(mant3); // powrot do postaci int np 1110010...0

    return result;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
IEEE16 IEEE16::mulLNS(IEEE16 num1, IEEE16 num2)
{
    IEEE16 result(0);
    std::cout << "LNS \n";
    // znak
    if (num1.sign != num2.sign) result.sign = 1;
    else result.sign = 0;

    //wykladnik
    result.exponent = (num1.exponent - 15) + num2.exponent;

    // mantysa
    float mant1 = ((float)num1.mantissa / 1024) + 1; // dzielimy przez 2^23 zeby bylo mniejsze niz 1 i inkrementujemy np 110...0 => 0.11 + 1 = 1.11
    float mant2 = ((float)num2.mantissa / 1024) + 1;

    float mant3 = powf(2, (log2(mant1) + log2(mant2)));

    if (mant3 > 2)
    {
        mant3 = mant3 / 2;
        result.exponent++;
        //std::cout << "pomnozone mantysy: " << mant3 << "\n";
    }
    //else std::cout << "podzielone mantysy: " << mant3 << "\n";

    result.mantissa = (int)((mant3 - 1) * 1024); // powrot do postaci int np 1110010...0

    return result;

}

//======================================================================================================================================================================================

//================================
// dzielenie
//================================
IEEE16 IEEE16::div(IEEE16 num1, IEEE16 num2)
{
    IEEE16 result(0);

    // znak
    if (num1.sign != num2.sign) result.sign = 1;
    else result.sign = 0;

    //wykladnik
    result.exponent = (num1.exponent + 15) - num2.exponent;

    // mantysa
    float mant1 = ((float)num1.mantissa / 1024) + 1; // dzielimy przez 2^23 zeby bylo mniejsze niz 1 i inkrementujemy np 110...0 => 0.11 + 1 = 1.11
    float mant2 = ((float)num2.mantissa / 1024) + 1;

    float mant3 = mant1 / mant2;

    if (mant3 < 1)
    {
        mant3 = mant3 * 2;
        result.exponent--;
        std::cout << "podzielone mantysy: " << mant3 << "\n";
    }
    //std::cout << "podzielone mantysy: " << mant3 << "\n";

    result.mantissa = (int)((mant3 - 1) * 1024); // powrot do postaci int np 1110010...0

    return result;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
IEEE16 IEEE16::divLNS(IEEE16 num1, IEEE16 num2)
{
    IEEE16 result(0);

    // znak
    if (num1.sign != num2.sign) result.sign = 1;
    else result.sign = 0;

    //wykladnik
    result.exponent = (num1.exponent + 15) - num2.exponent;

    // mantysa
    float mant1 = ((float)num1.mantissa / 1024) + 1; // dzielimy przez 2^23 zeby bylo mniejsze niz 1 i inkrementujemy np 110...0 => 0.11 + 1 = 1.11
    float mant2 = ((float)num2.mantissa / 1024) + 1;

    float mant3 = powf(2, (log2(mant1) - log2(mant2)));

    if (mant3 < 1)
    {
        mant3 = mant3 * 2;
        result.exponent--;
        //std::cout << "podzielone mantysy: " << mant3 << "\n";
    }
    //else std::cout << "podzielone mantysy: " << mant3 << "\n";

    result.mantissa = (int)((mant3 - 1) * 1024); // powrot do postaci int np 1110010...0

    return result;
}
//======================================================================================================================================================================================

//================================
// pierwiastek
//================================
void IEEE16::sr()
{
    if (this->sign == 0)
    {
        // wykladnik
        this->exponent = (this->exponent - 15) / 2 + 15;

        // mantysa
        float mant1 = ((float)this->mantissa / 1024) + 1; // dzielimy przez 2^23 zeby bylo mniejsze niz 1 i inkrementujemy np 110...0 => 0.11 + 1 = 1.11
        mant1 = sqrt(mant1);

        if (mant1 > 2)
        {
            mant1 = mant1 / 2;
            this->exponent++;
        }
        if (mant1 < 1)
        {
            mant1 = mant1 * 2;
            this->exponent--;
            std::cout << "Mantysa po pierwiastku: " << mant1 << "\n";
        }
        std::cout << "Mantysa po pierwiastku: " << std::fixed << mant1 << "\n";

        this->mantissa = (int)((mant1 - 1) * 1024); // powrot do postaci int np 1110010...0
    }
    else std::cout << "Ujemna liczba" << "\n";

}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
void IEEE16::srLNS()
{
    //code
    if (this->sign == 0)
    {
        // wykladnik
        this->exponent = (this->exponent - 15) / 2 + 15;

        // mantysa
        float mant1 = ((float)this->mantissa / 1024) + 1; // dzielimy przez 2^23 zeby bylo mniejsze niz 1 i inkrementujemy np 110...0 => 0.11 + 1 = 1.11

        mant1 = powf(2, (log2(mant1) / 2));

        if (mant1 > 2)
        {
            mant1 = mant1 / 2;
            this->exponent++;
        }
        if (mant1 < 1)
        {
            mant1 = mant1 * 2;
            this->exponent--;
        }

        std::cout << "Mantysa po pierwiastku: " << mant1 << "\n";

        this->mantissa = (int)((mant1 - 1) * 1024); // powrot do postaci int np 1110010...0
    }
    else std::cout << "Ujemna liczba" << "\n";

}
//======================================================================================================================================================================================

//================================
// odwrotnosc pierwiastka
//================================
void IEEE16::isr()
{
    if (this->sign == 0)
    {
        // wykladnik
        int exp = (int)this->exponent;
        exp = ((exp - 15) / -2 + 15);
        this->exponent = exp;

        // mantysa
        float mant1 = ((float)this->mantissa / 1024) + 1; // dzielimy przez 2^23 zeby bylo mniejsze niz 1 i inkrementujemy np 110...0 => 0.11 + 1 = 1.11

        mant1 = (sqrt(mant1));
        mant1 = powf(mant1, -1);

        if (mant1 > 2)
        {
            mant1 = mant1 / 2;
            this->exponent++;
        }
        if (mant1 < 1)
        {
            mant1 = mant1 * 2;
            this->exponent--;
        }
        std::cout << "Mantysa po pierwiastku: " << mant1 << "\n";

        this->mantissa = (int)((mant1 - 1) * 1024); // powrot do postaci int np 1110010...0
    }
    else std::cout << "Ujemna liczba" << "\n";
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
void IEEE16::isrLNS()
{
    if (this->sign == 0)
    {
        // wykladnik
        int exp = (int)this->exponent;
        exp = ((exp - 15) / -2 + 15);
        this->exponent = exp;

        // mantysa
        float mant1 = ((float)this->mantissa / 1024) + 1; // dzielimy przez 2^23 zeby bylo mniejsze niz 1 i inkrementujemy np 110...0 => 0.11 + 1 = 1.11

        mant1 = powf(2, (log2(mant1) / -2));

        if (mant1 > 2)
        {
            mant1 = mant1 / 2;
            this->exponent++;
        }
        if (mant1 < 1)
        {
            mant1 = mant1 * 2;
            this->exponent--;
        }
        std::cout << "Mantysa po pierwiastku: " << mant1 << "\n";

        this->mantissa = (int)((mant1 - 1) * 1024); // powrot do postaci int np 1110010...0
    }
    else std::cout << "Ujemna liczba" << "\n";
}