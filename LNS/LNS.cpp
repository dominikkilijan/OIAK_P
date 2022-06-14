// LNS.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
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
    float number1 = 25.456f;
    float number2 = 25.741f;
    long long int iterations = 10;
    
    IEEE32 num1(number1);
    //num1.sign = 0;
    //num1.exponent = 254;
    //num1.mantissa = 15110;
    num1.printNumber();

    IEEE32 num2(number2);
    //num2.sign = 0;
    //num2.exponent = 224;
    //num2.mantissa = 9159;
    num2.printNumber();

    IEEE32 num3;
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
    num1.fValue = number1;

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
    num1.fValue = number1;
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
    num1.fValue = number1;
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
    num1.fValue = number1;
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


}


long long int read_QPC()
{
    LARGE_INTEGER count;

    QueryPerformanceCounter(&count);
    return ((long long int)count.QuadPart);
}
// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
