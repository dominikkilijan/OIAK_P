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

unsigned int IEEE16::logConverter(unsigned int mantissaToLog)
{
    unsigned int mant = mantissaToLog;
    int a[] = {0,0};
    int b = 0;

    if (mant >= 0 && mant <= 95)
    {
        a[0] = 1;
        a[1] = -3;
        b = 13;
    }
    else if (mant >= 96 && mant <= 191)
    {
        a[0] = 2;
        a[1] = 6;
        b = 98;
    }
    else if (mant >= 192 && mant <= 303)
    {
        a[0] = 3;
        a[1] = 5;
        b = 269;
    }
    else if (mant >= 304 && mant <= 415)
    {
        a[0] = 4;
        a[1] = 0;
        b = 501;
    }
    else if (mant >= 416 && mant <= 569)
    {
        a[0] = -6;
        a[1] = 0;
        b = 763;
    }
    else if (mant >= 560 && mant <= 703)
    {
        a[0] = -3;
        a[1] = 6;
        b = 1178;
    }
    else if (mant >= 704 && mant <= 847)
    {
        a[0] = -2;
        a[1] = 4;
        b = 1622;
    }
    else if (mant >= 848 && mant <= 1023)
    {
        a[0] = -2;
        a[1] = 0;
        b = 2055;
    }

    mant = mant << 3;
    mant = mant + b;
    for (int i = 0; i < 2; i++)
    {
        if (a[i] > 0)
        {
            unsigned int mant2 = mantissaToLog << 3;
            mant2 = mant2 >> a[i];
            mant += mant2;
        }
        else if (a[i] < 0)
        {
            unsigned int mant2 = mantissaToLog << 3;
            mant2 = mant2 >> abs(a[i]);
            mant -= mant2;
        }
    }
    mant = mant >> 3;
    std::cout << "Mantysa po logConverter: " << mant << "\n";
    return mant;
}
unsigned int IEEE16::antilogConverter(unsigned int mantissaToLog)
{
    unsigned int mant = mantissaToLog;
    int a[] = {0,0};
    int b = 0;

    if (mant >= 0 && mant <= 159)
    {
        a[0] = -2;
        a[1] = -6;
        b = 8188;
    }
    else if (mant >= 160 && mant <= 287)
    {
        a[0] = -2;
        a[1] = 4;
        b = 8085;
    }
    else if (mant >= 288 && mant <= 431)
    {
        a[0] = -3;
        a[1] = 6;
        b = 7898;
    }
    else if (mant >= 432 && mant <= 575)
    {
        a[0] = -5;
        a[1] = 0;
        b = 7625;
    }
    else if (mant >= 576 && mant <= 703)
    {
        a[0] = 4;
        a[1] = 6;
        b = 7123;
    }
    else if (mant >= 704 && mant <= 815)
    {
        a[0] = 3;
        a[1] = 5;
        b = 6680;
    }
    else if (mant >= 816 && mant <= 943)
    {
        a[0] = 2;
        a[1] = 6;
        b = 5964;
    }
    else if (mant >= 944 && mant <= 1023)
    {
        a[0] = 1;
        a[1] = -3;
        b = 5131;
    }

    mant = mant << 3;
    mant = mant + b;
    for (int i = 0; i < 2; i++)
    {
        if (a[i] > 0)
        {
            unsigned int mant2 = mantissaToLog << 3;
            mant2 = mant2 >> a[i];
            mant += mant2;
        }
        else if (a[i] < 0)
        {
            unsigned int mant2 = mantissaToLog << 3;
            mant2 = mant2 >> abs(a[i]);
            mant2 = ~mant2;
            mant += mant2;
        }
    }
    mant = mant >> 3;
    std::cout << "Mantysa po antilogConverter: " << mant << "\n";
    return mant;
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
    IEEE16 result1(0);
    IEEE16 result2(0);
    std::cout << "LNS \n";
    // znak
    if (num1.sign != num2.sign) result.sign = 1;
    else result.sign = 0;

    //wykladnik
    result.exponent = (num1.exponent - 15) + num2.exponent;

    // mantysa
    //float mant1 = ((float)num1.mantissa / 1024) + 1; // dzielimy przez 2^23 zeby bylo mniejsze niz 1 i inkrementujemy np 110...0 => 0.11 + 1 = 1.11
    //float mant2 = ((float)num2.mantissa / 1024) + 1;
    //--------------------------------------------------------
    result1.mantissa = logConverter(num1.mantissa);
    result2.mantissa = logConverter(num2.mantissa);

    float mant11 = ((float)result1.mantissa / 1024) + 1;
    float mant22 = ((float)result2.mantissa / 1024) + 1;
    std::cout << "mant11: " << mant11 << "\n";
    std::cout << "mant11: " << mant22 << "\n";
    
    float mant3 = powf(2, mant11 + mant22);
    //float mant3 = (((float)antilogConverter(result1.mantissa + result2.mantissa) / 1024.0f) + 1.0f);
    std::cout << "mant3: " << mant3 << "\n";

    //--------------------------------------------------------
    //float mant3 = powf(2, (log2(mant1) + log2(mant2)));
    if (mant3 > 2) result.exponent++;
    while (mant3 > 2)
    {
        mant3 /= 2;
    }

    std::cout << "mant3: " << mant3 << "\n";

    //result.mantissa = (int)((mant3 - 1) * 1024); // powrot do postaci int np 1110010...0
    result.mantissa = (int)((mant3 - 1) * 1024);

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
    std::cout << "podzielone mantysy: " << mant3 << "\n";

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
    //float mant1 = ((float)num1.mantissa / 1024) + 1; // dzielimy przez 2^23 zeby bylo mniejsze niz 1 i inkrementujemy np 110...0 => 0.11 + 1 = 1.11
    //float mant2 = ((float)num2.mantissa / 1024) + 1;


    //--------------------------------------------------------
    IEEE16 result1(0);
    IEEE16 result2(0);
    result1.mantissa = logConverter(num1.mantissa);
    result2.mantissa = logConverter(num2.mantissa);
    std::cout << "result1.mantissa: " << result1.mantissa << "\n";
    std::cout << "result2.mantissa: " << result2.mantissa << "\n";


    float mant11 = ((float)result1.mantissa / 1024) + 1;
    float mant22 = ((float)result2.mantissa / 1024) + 1;
    float mant3 = powf(2, mant11 - mant22);
    /*float mant3;
    if (result1.mantissa < result2.mantissa)
    {
        mant3 = (1.0f / (((float)antilogConverter(result2.mantissa - result1.mantissa) / 1024.0f) + 1.0f));
    }
    else mant3 = (((float)antilogConverter(result1.mantissa - result2.mantissa) / 1024.0f) + 1.0f);*/
    std::cout << "mant3: " << mant3 << "\n";

    if (mant3 > 2)
    {
        mant3 /= 2;
        result.exponent--;
        //std::cout << "podzielone mantysy: " << mant3 << "\n";
    }
    if (mant3 < 1)
    {
        mant3 *= 2;
        result.exponent--;
        //std::cout << "podzielone mantysy: " << mant3 << "\n";
    }
    std::cout << "podzielone mantysy: " << mant3 << "\n";

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
        //float mant11 = ((float)this->mantissa / 1024) + 1; // dzielimy przez 2^23 zeby bylo mniejsze niz 1 i inkrementujemy np 110...0 => 0.11 + 1 = 1.11

        IEEE16 result1(0);
        result1.mantissa = logConverter(this->mantissa);
        float mant1 = ((float)antilogConverter(result1.mantissa / 2) / 1024) + 1;

        if (mant1 > 2)
        {
            mant1 = mant1 - 1;
        }

        std::cout << "2 Mantysa po pierwiastku: " << mant1 << "\n";

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

        IEEE16 result1(0);
        result1.mantissa = logConverter(this->mantissa);
        long k1 = (long)result1.mantissa / -2;
        float mant1 = ((float)antilogConverter(k1) / 1024) + 1.0f;
        /*if (mant1 > 2)
        {
            mant1 -= 1;
        }*/
        std::cout << "2 Mantysa po pierwiastku: " << mant1 << "\n";
        /*if (mant1 > 2)
        {
            mant1 /= 2;
            this->exponent--;
        }
        if (mant1 < 1)
        {
            mant1 *= 2;
            this->exponent--;
        }*/
        if (mant1 > 2)
        {
            mant1 -= 1;
            this->exponent--;
        }
        if (mant1 < 1)
        {
            mant1 += 1;
            this->exponent++;
        }
        std::cout << "2 Mantysa po pierwiastku: " << mant1 << "\n";
        /*float mant1 = ((float)this->mantissa / 1024) + 1; // dzielimy przez 2^23 zeby bylo mniejsze niz 1 i inkrementujemy np 110...0 => 0.11 + 1 = 1.11

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
        }*/
        std::cout << "Mantysa po pierwiastku: " << mant1 << "\n";

        this->mantissa = (int)((mant1 - 1) * 1024); // powrot do postaci int np 1110010...0
    }
    else std::cout << "Ujemna liczba" << "\n";
}

void IEEE16::isrLNSIdeal()
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
        //std::cout << "Mantysa po pierwiastku: " << mant1 << "\n";

        this->mantissa = (int)((mant1 - 1) * 1024); // powrot do postaci int np 1110010...
    }
    else std::cout << "Ujemna liczba" << "\n";
}
