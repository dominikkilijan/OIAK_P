// LNS.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include "IEEE32.h"
#include <bitset>

int main()
{
    float number1 = 6.9f;
    float number2 = 2.0f;
    
    IEEE32 num1(number1);
    num1.printNumber();

    IEEE32 num2(number2);
    num2.printNumber();

    IEEE32 num3;
//-----------------------------------------------------------------------------------------------------------------------------
    std::cout << "-----------------------------------------------------------------------------\n";
    std::cout << "Mnozenie\n";
    num3 = num3.mul(num1, num2);
    std::cout << "---------------------------\n";
    num3.printNumber();
    std::cout << "-----------------------------------------------------------------------------\n";
//-----------------------------------------------------------------------------------------------------------------------------
    std::cout << "-----------------------------------------------------------------------------\n";
    std::cout << "Mnozenie LNS\n";
    num3 = num3.mulLNS(num1, num2);
    std::cout << "---------------------------\n";
    num3.printNumber();
    std::cout << "-----------------------------------------------------------------------------\n";
//-----------------------------------------------------------------------------------------------------------------------------
    std::cout << "-----------------------------------------------------------------------------\n";
    std::cout << "Dzielenie\n";
    num3 = num3.div(num1, num2);
    std::cout << "---------------------------\n";
    num3.printNumber();
    std::cout << "-----------------------------------------------------------------------------\n";
//-----------------------------------------------------------------------------------------------------------------------------
    std::cout << "-----------------------------------------------------------------------------\n";
    std::cout << "Dzielenie LNS\n";
    num3 = num3.divLNS(num1, num2);
    std::cout << "---------------------------\n";
    num3.printNumber();
    std::cout << "-----------------------------------------------------------------------------\n";
//-----------------------------------------------------------------------------------------------------------------------------
    std::cout << "-----------------------------------------------------------------------------\n";
    std::cout << "Pierwiastek\n";
    num1.fValue = number1;
    num1.sr();
    std::cout << "---------------------------\n";
    num1.printNumber();
    std::cout << "-----------------------------------------------------------------------------\n";
//-----------------------------------------------------------------------------------------------------------------------------
    std::cout << "-----------------------------------------------------------------------------\n";
    std::cout << "Pierwiastek LNS\n";
    num1.fValue = number1;
    num1.srLNS();
    std::cout << "---------------------------\n";
    num1.printNumber();
    std::cout << "-----------------------------------------------------------------------------\n";
//-----------------------------------------------------------------------------------------------------------------------------
    std::cout << "-----------------------------------------------------------------------------\n";
    std::cout << "Odwrotnosc pierwiastka\n";
    num1.fValue = number1;
    num1.isr();
    std::cout << "---------------------------\n";
    num1.printNumber();
    std::cout << "-----------------------------------------------------------------------------\n";
//-----------------------------------------------------------------------------------------------------------------------------
    std::cout << "-----------------------------------------------------------------------------\n";
    std::cout << "Odwrotnosc pierwiastka LNS\n";
    num1.fValue = number1;
    num1.isrLNS();
    std::cout << "---------------------------\n";
    num1.printNumber();
    std::cout << "-----------------------------------------------------------------------------\n";
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
