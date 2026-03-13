#include "Header.h"
#include <iostream>
#include <string>
#include <vector>

// FIX_MEOW: добавлены более лаконичные комментарии

// FIX_MEOW: неправильные названия переменных

// Проверка, является ли строка числом
bool IsNumber(const std::string& Str)
{
    if (Str.empty())
    {
        return false;
    }

    for (char c : Str)
    {
        if (!isdigit(c))
        {
            return false;
        }
    }
    return true;
}

// Безопасное чтение целого числа из консоли с проверкой на корректность
bool SafeReadIntFromConsole(int& OutValue)
{
    std::string Input;
    std::cin >> Input;

    if (!IsNumber(Input))
    {
        std::cout << "Ошибка: Введено некорректное значение '" << Input << "'. Ожидалось число." << std::endl;
        return false;
    }

    OutValue = std::stoi(Input);
    return true;
}

void SolveKBaseTask()
{
    int K, N;

    std::cout << "Введите систему счисления K (2 <= K <= 10): ";
    if (!SafeReadIntFromConsole(K))
    {
        return;
    }

    std::cout << "Введите количество разрядов N (1 < N < 20): ";
    if (!SafeReadIntFromConsole(N))
    {
        return;
    }

    // Валидация согласно условию задачи
    if (K < 2 || K > 10 || N <= 1 || N >= 20 || (N + K) >= 26)
    {
        std::cout << "Ошибка: Некорректные параметры (проверьте диапазоны K, N и условие N + K < 26)." << std::endl;
        return;
    }

    /* Инициализация счетчиков для чисел первого разряда (i=1)
     Число не может начинаться с нуля (кроме случая N=1, но N > 1)
    */
    // float nz, oz, tz, thz, i, _nz, _oz, _tz, _thz, foz, _foz;
    // (использован double для минимизации погрешности при больших N и K)
    double NoZeroCount = K - 1; // Заканчивается не на ноль
    double OneZeroCount = 0;    // Заканчивается на 1 ноль (первая цифра не 0)
    double TwoZeroCount = 0;
    double ThreeZeroCount = 0;
    double FourOrMoreZeroCount = 0;

    // Перебор разрядов со второго по N
    // for (i = 2; i <= N; i++)
    for (int DigitIndex = 2; DigitIndex <= N; DigitIndex++)
    {
        double PrevNoZeroCount = NoZeroCount;
        double PrevOneZeroCount = OneZeroCount;
        double PrevTwoZeroCount = TwoZeroCount;
        double PrevThreeZeroCount = ThreeZeroCount;
        double PrevFourOrMoreZeroCount = FourOrMoreZeroCount;

        // Если добавляем не ноль (K-1 вариант), любое число теперь "не заканчивается на ноль"
        // FIX_MEOW: не вынесен общий множитель
        // nz = _nz * (K - 1) + _oz * (K - 1) + _thz * (K - 1) + _tz * (K - 1) + _foz * (K - 1); //нет нулей на конце
        NoZeroCount = (PrevNoZeroCount + PrevOneZeroCount + PrevTwoZeroCount +
            PrevThreeZeroCount + PrevFourOrMoreZeroCount) * (K - 1);

        // Если добавляем ноль:
        OneZeroCount = PrevNoZeroCount;       // Был не ноль -> стал один ноль
        TwoZeroCount = PrevOneZeroCount;      // Был один -> стало два
        ThreeZeroCount = PrevTwoZeroCount;    // Было два -> стало три

        /* Если уже было 4+ нулей, любая следующая цифра (K вариантов) сохраняет это свойство.
        Если было ровно 3 нуля в конце и добавили еще один (1 вариант), стало 4.
        */
        FourOrMoreZeroCount = (PrevFourOrMoreZeroCount * K) + PrevThreeZeroCount;
    }
    std::cout << "Количество чисел, содержащих более трех идущих нулей подряд: " << FourOrMoreZeroCount << std::endl;
}