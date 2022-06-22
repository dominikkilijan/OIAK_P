#include "IEEE16.h"
#include "IEEE32.h"
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
    std::cout << "Poczatkowa mantysa: " << mant << "\n";
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
    std::cout << "b = " << b << "\n";
    mant = mant << 3;
    std::cout << "mant po przesunieciu = " << mant << "\n";
    mant = mant + b;
    std::cout << "mant plus b = " << mant << "\n";
    for (int i = 0; i < 2; i++)
    {
        std::cout << "a[i] = " << a[i] << "\n";
        if (a[i] > 0)
        {
            unsigned int mant2 = mantissaToLog << 3;
            mant2 = mant2 >> a[i];
            std::cout << "mant2 po przesunieciu = " << mant2 << "\n";
            mant += mant2;
            std::cout << "mant po dodaniu mant2 = " << mant << "\n";
        }
        else if (a[i] < 0)
        {
            unsigned int mant2 = mantissaToLog << 3;
            mant2 = mant2 >> abs(a[i]);
            mant2 = ~mant2;
            std::cout << "mant2 po przesunieciu = " << mant2 << "\n";
            mant += mant2;
            std::cout << "mant po dodaniu mant2 = " << mant << "\n";
        }
    }
    mant & 8191;
    mant = mant >> 3;
    std::cout << "Mantysa po antilogConverter: " << (mant) << "\n";
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
    }


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
    result1.mantissa = logConverter(num1.mantissa);
    result2.mantissa = logConverter(num2.mantissa);

    float mant11 = ((float)result1.mantissa / 1024) + 1;
    float mant22 = ((float)result2.mantissa / 1024) + 1;
    float mant3 = powf(2, mant11 + mant22);

    if (mant3 > 2) result.exponent++;
    while (mant3 > 2)
    {
        mant3 /= 2;
    }

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
    }

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

    IEEE16 result1(0);
    IEEE16 result2(0);
    result1.mantissa = logConverter(num1.mantissa);
    result2.mantissa = logConverter(num2.mantissa);

    float mant11 = ((float)result1.mantissa / 1024) + 1;
    float mant22 = ((float)result2.mantissa / 1024) + 1;
    float mant3 = powf(2, mant11 - mant22);

    if (mant3 > 2)
    {
        mant3 /= 2;
        result.exponent--;
    }
    if (mant3 < 1)
    {
        mant3 *= 2;
        result.exponent--;
    }

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
        }

        this->mantissa = (int)((mant1 - 1) * 1024); // powrot do postaci int np 1110010...0
    }
    else std::cout << "Ujemna liczba" << "\n";

}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
void IEEE16::srLNS()
{
    if (this->sign == 0)
    {
        // wykladnik
        this->exponent = (this->exponent - 15) / 2 + 15;

        // mantysa
        IEEE16 result1(0);
        result1.mantissa = logConverter(this->mantissa);
        float mant1 = ((float)antilogConverter(result1.mantissa / 2) / 1024) + 1;

        if (mant1 > 2)
        {
            mant1 = mant1 - 1;
        }

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
        float mulMant = 1;
        // wykladnik
        float exp = (float)this->exponent;
        exp = ((exp - 15) / -2);

        if (exp - (int)exp != 0)
        {
            mulMant = sqrt(2);
            exp -= 1;
        }
        
        std::cout << "mulMant = " << mulMant << "\n";
        this->exponent = (int)exp + 15;
        std::cout << "Exponent = " << exp << "\n";

        // mantysa
        float mant1 = ((float)this->mantissa / 1024) + 1; // dzielimy przez 2^23 zeby bylo mniejsze niz 1 i inkrementujemy np 110...0 => 0.11 + 1 = 1.11
        std::cout << "Mantysa = " << mant1 << "\n";
        mant1 = (sqrt(mant1));
        std::cout << "Mantysa po pierwiastku = " << mant1 << "\n";
        mant1 = powf(mant1, -1);
        std::cout << "Mantysa po odwrotnoœci = " << mant1 << "\n";
        
        mant1 *= mulMant;
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
        std::cout << "Mantysa po ewentualnej poprawie: " << mant1 << "\n";
        std::cout << "Exponent po ewentualnej poprawie = " << exp << "\n";

        this->mantissa = (int)((mant1 - 1) * 1024); // powrot do postaci int np 1110010...0
    }
    else std::cout << "Ujemna liczba" << "\n";
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
void IEEE16::isrLNS()
{
    if (this->sign == 0)
    {
        float mulMant = 1;
        // wykladnik
        float exp = (float)this->exponent;
        exp = ((exp - 15) / -2);

        if (exp - (int)exp != 0)
        {
            mulMant = sqrt(2);
            exp -= 1;
        }
        std::cout << "mulMant: " << mulMant << "\n";
        this->exponent = (int)exp + 15;
        std::cout << "Exponent = " << exp << "\n";

        // mantysa
        /*float mant1 = ((float)this->mantissa / 1024) + 1; // dzielimy przez 2^23 zeby bylo mniejsze niz 1 i inkrementujemy np 110...0 => 0.11 + 1 = 1.11
        std::cout << "Mantysa: " << mant1 << "\n";
        
        float k1 = logConverter((float)this->mantissa);// / 1024 + 1.0f;
        std::cout << "k1: " << k1 << "\n";
        k1 = k1 / 1024 + 1;
        std::cout << "k1: " << k1 << "\n";
        mant1 = powf(2, k1 / -2);
        std::cout << "Mantysa po 2^log2: " << mant1 << "\n";
        mant1 *= mulMant;
        mant1 *= mulMant;
        std::cout << "Mantysa mulMant: " << mant1 << "\n";*/
        IEEE16 result1(0);
        result1.mantissa = logConverter(this->mantissa);
        long k1 = (long)result1.mantissa / -2;
        float mant1 = ((float)antilogConverter(k1) / 1024) + 1.0f;
        mant1 *= mulMant;
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

        this->mantissa = (int)((mant1 - 1) * 1024); // powrot do postaci int np 1110010...
    }
    else std::cout << "Ujemna liczba" << "\n";
}

void IEEE16::isrLNSIdeal()
{
    if (this->sign == 0)
    {
        float mulMant = 1;
        // wykladnik
        float exp = (float)this->exponent;
        exp = ((exp - 15) / -2);

        if (exp - (int)exp != 0)
        {
            mulMant = sqrt(2);
            exp -= 1;
        }
        std::cout << "mulMant: " << mulMant << "\n";
        this->exponent = (int)exp + 15;
        std::cout << "Exponent = " << exp << "\n";

        // mantysa
        float mant1 = ((float)this->mantissa / 1024) + 1; // dzielimy przez 2^23 zeby bylo mniejsze niz 1 i inkrementujemy np 110...0 => 0.11 + 1 = 1.11
        std::cout << "Mantysa: " << mant1 << "\n";
        mant1 = powf(2, (log2(mant1) / -2));
        std::cout << "Mantysa po 2^log2: " << mant1 << "\n";
        mant1 *= mulMant;
        std::cout << "Mantysa mulMant: " << mant1 << "\n";

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

        this->mantissa = (int)((mant1 - 1) * 1024); // powrot do postaci int np 1110010...
    }
    else std::cout << "Ujemna liczba" << "\n";
}
