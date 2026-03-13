//Во всех заданиях данной подгруппы предполагается, что исходные строки, определяющие выражения, 
//не содержат пробелов.При выполнении заданий не следует использовать оператор цикла.
//Вывести значение логического выражения, заданного в виде строки S.Выражение определяется следующим 
//образом(«T» — True, «F» — False) :
//	<выражение> :: = T | F | And(<выражение>, <выражение>) | Or(<выражение>, <выражение>)

#include "Header.h"
#include <iostream>
#include <string>
#include <Windows.h>

// using namespace std; FIX_MEOW: использование глобального пространства имён

// FIX_MEOW: всё реализовано в main

int main()
{
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::string ExpressionString;
    std::cout << "Введите логическое выражение (T, F, And(,), Or(,)): ";

    if (!std::getline(std::cin, ExpressionString) || ExpressionString.empty())
    {
        std::cout << "Ошибка: Введена пустая строка." << std::endl;
        return 1;
    }

    // Рекурсивная валидация отсутствия пробелов
    if (HasSpaces(ExpressionString, 0))
    {
        std::cout << "Ошибка: Выражение содержит пробелы." << std::endl;
        return 1;
    }

    int PositionIndex = 0;
    // bool res = ParseExpression(ExpressionString, PositionIndex);
    bool ResultValue = ParseLogicalExpression(ExpressionString, PositionIndex);

    // if (res == true) FIX_MEOW: лишнее сравнение с true
    // Вывод результата
    std::cout << "Значение логического выражения: " << (ResultValue ? "T" : "F") << std::endl;

    return 0;
}