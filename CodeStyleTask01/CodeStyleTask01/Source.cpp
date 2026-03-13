#include "Header.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <sstream>
#include <string>

// FIX_MEOW: отсутствие проверок входных данных

// Проверка, является ли строка корректным числом
bool IsNumber(const std::string& Str)
{
    if (Str.empty())
    {
        return false;
    }

    size_t Start = 0;
    if (Str[0] == '-')
    {
        Start = 1; // Начинаем со второго символа, если число отрицательное
    }

    for (size_t i = Start; i < Str.length(); i++)
    {
        if (!isdigit(Str[i]))
        {
            return false;
        }
    }
    return true;
}

// Безопасное чтение целого числа из потока с проверкой ошибок
bool SafeReadInt(std::ifstream& File, int& Value, int LineNum)
{
    std::string Token;
    File >> Token;

    if (File.fail() || Token.empty())
    {
        std::cout << "Ошибка: Не удалось прочитать число в строке " << LineNum << std::endl;
        return false;
    }

    if (!IsNumber(Token))
    {
        std::cout << "Ошибка: в файле обнаружен лишний символ '" << Token << " вместо числа в строке " << LineNum << std::endl;
        return false;
    }

    Value = std::stoi(Token);
    return true;
}

// Проверка соответствия кол-ва чисел в строке
bool HasEnoughNumberInLine(std::ifstream& File, int RequiredCount, int LineNum)
{
    std::streampos CurrentPos = File.tellg();
    std::string Line;
    std::getline(File, Line);

    if (File.fail())
    {
        return false;
    }

    std::stringstream SS(Line);
    std::string Token;
    int Count = 0;

    while (SS >> Token)
    {
        if (IsNumber(Token))
        {
            Count++;
        }
        else
        {
            std::cout << "Ошибка: В строке " << LineNum << " обнаружен неверный символ '" << Token << "'" << std::endl;
            return false;
        }
    }

    if (Count != RequiredCount)
    {
        std::cout << "Ошибка: В строке " << LineNum << " должно быть " << RequiredCount << " чисел, найдено " << Count << std::endl;
        return false;
    }

    File.clear();
    File.seekg(CurrentPos);
    return true;
}

// void BackRec4() { // FIX_MEOW: некорректное название функции
void SolveArtefacts()
{
    std::ifstream InputFile("f.txt");
    if (!InputFile.is_open())
        // FIX_MEOW: отсутствие выхода при ошибке открытия файла
    {
        std::cout << "Файл не найден." << std::endl;
        return;
    }
    int N, A, B;
    int LineNum = 1;

    // Чтение первой строки (N, A, B)
    if (!SafeReadInt(InputFile, N, LineNum) ||
        !SafeReadInt(InputFile, A, LineNum) ||
        !SafeReadInt(InputFile, B, LineNum))
    {
        std::cout << "Ошибка: Некорректные параметры N, A или B." << std::endl;
        return;
    }

    if (N <= 0 || A < 0 || B < A)
    {
        std::cout << "Ошибка: Некорректные параметры N, A или B." << std::endl;
        return;
    }

    // Пропускаем остаток первой строки
    std::string Skip;
    std::getline(InputFile, Skip);

    // std::vector<int> c(N), d(N); // FIX_MEOW: некорректное название векторов
    // Чтение весов (строка 2)
    LineNum = 2;
    if (!HasEnoughNumberInLine(InputFile, N, LineNum))
    {
        std::cout << "Ошибка: Некорректное количество весов." << std::endl;
        return;
    }

    std::vector<int> ItemWeights;
    for (int i = 0; i < N; i++)
    {
        int Val;
        if (!SafeReadInt(InputFile, Val, LineNum)) 
        {
            return;
        }
        if (Val < 0)
        {
            std::cout << "Ошибка: Вес не может быть отрицательным." << std::endl;
            return;
        }
        ItemWeights.push_back(Val);
    }

    // Чтение объемов (строка 3)
    std::getline(InputFile, Skip); // Пропуск конца строки
    LineNum = 3;
    if (!HasEnoughNumberInLine(InputFile, N, LineNum))
    {
        std::cout << "Ошибка: Некорректное количество объёмов." << std::endl;
        return;
    }

    std::vector<int> ItemVolumes;
    for (int i = 0; i < N; i++)
    {
        int Val;
        if (!SafeReadInt(InputFile, Val, LineNum))
        {
            return;
        }
        if (Val < 0)
        {
            std::cout << "Ошибка: Объем не может быть отрицательным." << std::endl;
            return;
        }
        ItemVolumes.push_back(Val);
    }
    InputFile.close();

   // Алгоритм Рюкзака (минимизация объема для веса в диапазоне [A, B])
   // Используем B как максимально возможный вес
    // FIX_MEOW: неверные названия переменных и векторов
    std::vector<int> MinVolumeForWeight(B + 1, INT_MAX);
    MinVolumeForWeight[0] = 0;

    // Добавлена матрица для восстановления выбранных предметов
    std::vector<std::vector<bool>> Selected(B + 1, std::vector<bool>(N, false));
    for (int i = 0; i < N; i++)
    {
        for (int w = B; w >= ItemWeights[i]; w--)
        {
            if (MinVolumeForWeight[w - ItemWeights[i]] != INT_MAX)
            {
                int NewVolume = MinVolumeForWeight[w - ItemWeights[i]] + ItemVolumes[i];
                if (NewVolume < MinVolumeForWeight[w])
                {
                    MinVolumeForWeight[w] = NewVolume;
                    Selected[w] = Selected[w - ItemWeights[i]];
                    Selected[w][i] = true;
                }
            }
        }
    }

    // Поиск оптимального веса в диапазоне [A, B]
    int MinTotalVolume = INT_MAX;
    int BestWeight = -1;

    for (int w = A; w <= B; w++)
    {
        if (MinVolumeForWeight[w] < MinTotalVolume)
        {
            MinTotalVolume = MinVolumeForWeight[w];
            BestWeight = w;
        }
    }

    if (BestWeight == -1)
    {
        std::cout << "Решение не найдено в заданном диапазоне весов." << std::endl;
    }
    else
    {
        std::cout << "Минимальный объем: " << MinTotalVolume << " куб.см" << std::endl;
        std::cout << "Общий вес: " << BestWeight << " кг" << std::endl;
        std::cout << "Порядковые номера артефактов: ";
        for (int i = 0; i < N; i++)
        {
            if (Selected[BestWeight][i])
            {
                std::cout << i + 1 << " ";
            }
        }
        std::cout << std::endl;
    }
}
