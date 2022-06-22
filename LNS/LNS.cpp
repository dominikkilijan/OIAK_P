// LNS.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include "IEEE16.h"
#include "IEEE32.h"
#include <bitset>
#include <iomanip>
#include <windows.h>

// mierzenie czasu
long long int read_QPC();
long long int frequency;
long long int start;
long long int elapsed;

int main()
{
    float number1 = 969.81f;
    float number2 = 69.81f;
    long long int iterations = 1;
   

    IEEE32 num132(number1);
    //num132.sign = 0;
    //num132.exponent = 30;
    //num132.mantissa = 487;
    //num132.printNumber();



    IEEE32 num232(number2);
    //num232.sign = 0;
    //num232.exponent = 224;
    //num232.mantissa = 9159;
    //num232.printNumber();

    IEEE16 num1(num132);
    //num1.sign = 0;
    //num1.exponent = 18;
    //num1.mantissa = 487;
    num1.printNumber();

    IEEE16 num2(num232);
    //num2.sign = 0;
    //num2.exponent = 18;
    //num2.mantissa = 487;
    num2.printNumber();

    IEEE32 num332;
    IEEE16 num3;

//-----------------------------------------------------------------------------------------------------------------------------
    std::cout << "-----------------------------------------------------------------------------\n";
    std::cout << "Mnozenie\n";

    QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
    start = read_QPC();  // poczatek pomiaru czasu
    
    num3 = num3.mul(num1, num2);

    elapsed = read_QPC() - start; // koniec pomiaru czasu
    elapsed = elapsed / iterations;

    std::cout << "Time [us] = " << std::fixed << std::setprecision(0) << (1000000.0 * elapsed) / frequency << "\n";
    std::cout << "Time [ns] = " << std::setprecision(0) << (1000000000.0 * elapsed) / frequency << "\n";
    std::cout << "---------------------------\n";
    num3.printNumber();
    std::cout << "-----------------------------------------------------------------------------\n";
//-----------------------------------------------------------------------------------------------------------------------------
    std::cout << "-----------------------------------------------------------------------------\n";
    std::cout << "Mnozenie LNS\n";
    QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
    start = read_QPC();  // poczatek pomiaru czasu

    num3 = num3.mulLNS(num1, num2);

    elapsed = read_QPC() - start; // koniec pomiaru czasu
    elapsed = elapsed / iterations;

    std::cout << "Time [us] = " << std::fixed << std::setprecision(0) << (1000000.0 * elapsed) / frequency << "\n";
    std::cout << "Time [ns] = " << std::setprecision(0) << (1000000000.0 * elapsed) / frequency << "\n";
    std::cout << "---------------------------\n";
    num3.printNumber();
    std::cout << "-----------------------------------------------------------------------------\n";


//-----------------------------------------------------------------------------------------------------------------------------
    std::cout << "-----------------------------------------------------------------------------\n";
    std::cout << "Dzielenie\n";
    QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
    start = read_QPC();  // poczatek pomiaru czasu

    num3 = num3.div(num1, num2);

    elapsed = read_QPC() - start; // koniec pomiaru czasu
    elapsed = elapsed / iterations;

    std::cout << "Time [us] = " << std::fixed << std::setprecision(0) << (1000000.0 * elapsed) / frequency << "\n";
    std::cout << "Time [ns] = " << std::setprecision(0) << (1000000000.0 * elapsed) / frequency << "\n";
    std::cout << "---------------------------\n";
    num3.printNumber();
    std::cout << "-----------------------------------------------------------------------------\n";
//-----------------------------------------------------------------------------------------------------------------------------
    std::cout << "-----------------------------------------------------------------------------\n";
    std::cout << "Dzielenie LNS\n";
    QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
    start = read_QPC();  // poczatek pomiaru czasu

    num3 = num3.divLNS(num1, num2);

    elapsed = read_QPC() - start; // koniec pomiaru czasu
    elapsed = elapsed / iterations;

    std::cout << "Time [us] = " << std::fixed << std::setprecision(0) << (1000000.0 * elapsed) / frequency << "\n";
    std::cout << "Time [ns] = " << std::setprecision(0) << (1000000000.0 * elapsed) / frequency << "\n";

    std::cout << "---------------------------\n";
    num3.printNumber();
    std::cout << "-----------------------------------------------------------------------------\n";


    //-----------------------------------------------------------------------------------------------------------------------------
    std::cout << "-----------------------------------------------------------------------------\n";
    std::cout << "Pierwiastek\n";
    num1.setValue(number1);

    QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
    start = read_QPC();  // poczatek pomiaru czasu

    num1.sr();

    elapsed = read_QPC() - start; // koniec pomiaru czasu
    elapsed = elapsed / iterations;

    std::cout << "Time [us] = " << std::fixed << std::setprecision(0) << (1000000.0 * elapsed) / frequency << "\n";
    std::cout << "Time [ns] = " << std::setprecision(0) << (1000000000.0 * elapsed) / frequency << "\n";

    std::cout << "---------------------------\n";
    num1.printNumber();
    std::cout << "-----------------------------------------------------------------------------\n";
//-----------------------------------------------------------------------------------------------------------------------------
    std::cout << "-----------------------------------------------------------------------------\n";
    std::cout << "Pierwiastek LNS\n";
    num1.setValue(number1);
    QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
    start = read_QPC();  // poczatek pomiaru czasu

    num1.srLNS();

    elapsed = read_QPC() - start; // koniec pomiaru czasu
    elapsed = elapsed / iterations;

    std::cout << "Time [us] = " << std::fixed << std::setprecision(0) << (1000000.0 * elapsed) / frequency << "\n";
    std::cout << "Time [ns] = " << std::setprecision(0) << (1000000000.0 * elapsed) / frequency << "\n";

    std::cout << "---------------------------\n";
    num1.printNumber();
    std::cout << "-----------------------------------------------------------------------------\n";


//-----------------------------------------------------------------------------------------------------------------------------
    std::cout << "-----------------------------------------------------------------------------\n";
    std::cout << "Odwrotnosc pierwiastka\n";
    num1.setValue(number1);
    QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
    start = read_QPC();  // poczatek pomiaru czasu

    num1.isr();

    elapsed = read_QPC() - start; // koniec pomiaru czasu
    elapsed = elapsed / iterations;

    std::cout << "Time [us] = " << std::fixed << std::setprecision(0) << (1000000.0 * elapsed) / frequency << "\n";
    std::cout << "Time [ns] = " << std::setprecision(0) << (1000000000.0 * elapsed) / frequency << "\n";

    std::cout << "---------------------------\n";
    num1.printNumber();
    std::cout << "-----------------------------------------------------------------------------\n";
//-----------------------------------------------------------------------------------------------------------------------------
    std::cout << "-----------------------------------------------------------------------------\n";
    std::cout << "Odwrotnosc pierwiastka LNS\n";
    num1.setValue(number1);
    QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
    start = read_QPC();  // poczatek pomiaru czasu

    num1.isrLNS();

    elapsed = read_QPC() - start; // koniec pomiaru czasu
    elapsed = elapsed / iterations;

    std::cout << "Time [us] = " << std::fixed << std::setprecision(0) << (1000000.0 * elapsed) / frequency << "\n";
    std::cout << "Time [ns] = " << std::setprecision(0) << (1000000000.0 * elapsed) / frequency << "\n";

    std::cout << "---------------------------\n";
    num1.printNumber();
    std::cout << "-----------------------------------------------------------------------------\n";
//-----------------------------------------------------------------------------------------------------------------------------
    std::cout << "-----------------------------------------------------------------------------\n";
    std::cout << "Odwrotnosc pierwiastka LNS\nMetoda z wykorzystaniem log()\n";
    num2.setValue(number1);

    num2.isrLNSIdeal();

    std::cout << "---------------------------\n";
    num2.printNumber();
    std::cout << "-----------------------------------------------------------------------------\n";

//=============================================================================================================================
// Bład bezwzględny mantysy ISR
//=============================================================================================================================
    unsigned int mantissaAbsoluteError = abs((int)num1.mantissa - (int)num2.mantissa);
    std::cout << "-----------------------------------------------------------------------------\n";
    std::cout << "Blad bezwzgledny mantys: " << mantissaAbsoluteError << "\n";

//=============================================================================================================================
// Bład bezwzgledny ISR liczby
//=============================================================================================================================
    float n1 = num1.toFloat();
    std::cout << n1 << "\n";
    float n2 = num2.toFloat();
    std::cout << n2 << "\n";
    float AbsoluteError = abs(n1 - n2);
    std::cout << "Blad bezwzgledny liczb: " << AbsoluteError << "\n";
    std::cout << "-----------------------------------------------------------------------------\n";

////=============================================================================================================================
////=============================================================================================================================
//// 32 bity
////=============================================================================================================================
////=============================================================================================================================
//
////-----------------------------------------------------------------------------------------------------------------------------
//    std::cout << "-----------------------------------------------------------------------------\n";
//    std::cout << "Mnozenie\n";
//
//    QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
//    start = read_QPC();  // poczatek pomiaru czasu
//    
//    num332 = num332.mul(num132, num232);
//
//    elapsed = read_QPC() - start; // koniec pomiaru czasu
//    elapsed = elapsed / iterations;
//
//    std::cout << "Time [us] = " << std::fixed << std::setprecision(0) << (1000000.0 * elapsed) / frequency << "\n";
//    std::cout << "Time [ns] = " << std::setprecision(0) << (1000000000.0 * elapsed) / frequency << "\n";
//    std::cout << "---------------------------\n";
//    num332.printNumber();
//    std::cout << "-----------------------------------------------------------------------------\n";
////-----------------------------------------------------------------------------------------------------------------------------
//    std::cout << "-----------------------------------------------------------------------------\n";
//    std::cout << "Mnozenie LNS\n";
//    QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
//    start = read_QPC();  // poczatek pomiaru czasu
//
//    num332 = num332.mulLNS(num132, num232);
//
//    elapsed = read_QPC() - start; // koniec pomiaru czasu
//    elapsed = elapsed / iterations;
//
//    std::cout << "Time [us] = " << std::fixed << std::setprecision(0) << (1000000.0 * elapsed) / frequency << "\n";
//    std::cout << "Time [ns] = " << std::setprecision(0) << (1000000000.0 * elapsed) / frequency << "\n";
//    std::cout << "---------------------------\n";
//    num332.printNumber();
//    std::cout << "-----------------------------------------------------------------------------\n";
//
//
////-----------------------------------------------------------------------------------------------------------------------------
//    std::cout << "-----------------------------------------------------------------------------\n";
//    std::cout << "Dzielenie\n";
//    QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
//    start = read_QPC();  // poczatek pomiaru czasu
//
//    num332 = num332.div(num132, num232);
//
//    elapsed = read_QPC() - start; // koniec pomiaru czasu
//    elapsed = elapsed / iterations;
//
//    std::cout << "Time [us] = " << std::fixed << std::setprecision(0) << (1000000.0 * elapsed) / frequency << "\n";
//    std::cout << "Time [ns] = " << std::setprecision(0) << (1000000000.0 * elapsed) / frequency << "\n";
//    std::cout << "---------------------------\n";
//    num332.printNumber();
//    std::cout << "-----------------------------------------------------------------------------\n";
////-----------------------------------------------------------------------------------------------------------------------------
//    std::cout << "-----------------------------------------------------------------------------\n";
//    std::cout << "Dzielenie LNS\n";
//    QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
//    start = read_QPC();  // poczatek pomiaru czasu
//
//    num3 = num332.divLNS(num132, num232);
//
//    elapsed = read_QPC() - start; // koniec pomiaru czasu
//    elapsed = elapsed / iterations;
//
//    std::cout << "Time [us] = " << std::fixed << std::setprecision(0) << (1000000.0 * elapsed) / frequency << "\n";
//    std::cout << "Time [ns] = " << std::setprecision(0) << (1000000000.0 * elapsed) / frequency << "\n";
//
//    std::cout << "---------------------------\n";
//    num332.printNumber();
//    std::cout << "-----------------------------------------------------------------------------\n";
//
//
////-----------------------------------------------------------------------------------------------------------------------------
//    std::cout << "-----------------------------------------------------------------------------\n";
//    std::cout << "Pierwiastek\n";
//    num132.fValue = number1;
//
//    QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
//    start = read_QPC();  // poczatek pomiaru czasu
//
//    num132.sr();
//
//    elapsed = read_QPC() - start; // koniec pomiaru czasu
//    elapsed = elapsed / iterations;
//
//    std::cout << "Time [us] = " << std::fixed << std::setprecision(0) << (1000000.0 * elapsed) / frequency << "\n";
//    std::cout << "Time [ns] = " << std::setprecision(0) << (1000000000.0 * elapsed) / frequency << "\n";
//
//    std::cout << "---------------------------\n";
//    num132.printNumber();
//    std::cout << "-----------------------------------------------------------------------------\n";
////-----------------------------------------------------------------------------------------------------------------------------
//    std::cout << "-----------------------------------------------------------------------------\n";
//    std::cout << "Pierwiastek LNS\n";
//    num132.fValue = number1;
//    QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
//    start = read_QPC();  // poczatek pomiaru czasu
//
//    num132.srLNS();
//
//    elapsed = read_QPC() - start; // koniec pomiaru czasu
//    elapsed = elapsed / iterations;
//
//    std::cout << "Time [us] = " << std::fixed << std::setprecision(0) << (1000000.0 * elapsed) / frequency << "\n";
//    std::cout << "Time [ns] = " << std::setprecision(0) << (1000000000.0 * elapsed) / frequency << "\n";
//
//    std::cout << "---------------------------\n";
//    num132.printNumber();
//    std::cout << "-----------------------------------------------------------------------------\n";
//
//
////-----------------------------------------------------------------------------------------------------------------------------
//    std::cout << "-----------------------------------------------------------------------------\n";
//    std::cout << "Odwrotnosc pierwiastka\n";
//    num132.fValue = number1;
//    QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
//    start = read_QPC();  // poczatek pomiaru czasu
//
//    num132.isr();
//
//    elapsed = read_QPC() - start; // koniec pomiaru czasu
//    elapsed = elapsed / iterations;
//
//    std::cout << "Time [us] = " << std::fixed << std::setprecision(0) << (1000000.0 * elapsed) / frequency << "\n";
//    std::cout << "Time [ns] = " << std::setprecision(0) << (1000000000.0 * elapsed) / frequency << "\n";
//
//    std::cout << "---------------------------\n";
//    num132.printNumber();
//    std::cout << "-----------------------------------------------------------------------------\n";
////-----------------------------------------------------------------------------------------------------------------------------
//    std::cout << "-----------------------------------------------------------------------------\n";
//    std::cout << "Odwrotnosc pierwiastka LNS\n";
//    num132.fValue = number1;
//    QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
//    start = read_QPC();  // poczatek pomiaru czasu
//
//    num132.isrLNS();
//
//    elapsed = read_QPC() - start; // koniec pomiaru czasu
//    elapsed = elapsed / iterations;
//
//    std::cout << "Time [us] = " << std::fixed << std::setprecision(0) << (1000000.0 * elapsed) / frequency << "\n";
//    std::cout << "Time [ns] = " << std::setprecision(0) << (1000000000.0 * elapsed) / frequency << "\n";
//
//    std::cout << "---------------------------\n";
//    num132.printNumber();
//    std::cout << "-----------------------------------------------------------------------------\n";


}


long long int read_QPC()
{
    LARGE_INTEGER count;

    QueryPerformanceCounter(&count);
    return ((long long int)count.QuadPart);
}
