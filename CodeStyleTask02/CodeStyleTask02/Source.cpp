#include "Header.h"
#include <iostream>
#include <sstream>
#include <algorithm>

// FIX_MEOW: некорректные названия переменных, векторов

// FIX_MEOW: отсутствие проверок на открытие файлов

// FIX_MEOW: добавлены более содержательные комментарии

// FIX_MEOW: расширена проверка на входные данные

// Проверка, является ли строка корректным числом
bool IsNumber(const std::string & Str)
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
    if (!(File >> Token))
    {
        std::cout << "Ошибка: Не удалось прочитать данные в строке " << LineNum << std::endl;
        return false;
    }

    if (!IsNumber(Token))
    {
        std::cout << "Ошибка: В строке " << LineNum << " найдено '" << Token << "' вместо числа." << std::endl;
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

    if (File.fail() && !File.eof())
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
            std::cout << "Ошибка: В строке " << LineNum << " обнаружен некорректный символ '" << Token << "'" << std::endl;
            return false;
        }
    }

    if (Count != RequiredCount)
    {
        std::cout << "Ошибка: В строке " << LineNum << " ожидалось " << RequiredCount << " чисел, найдено " << Count << std::endl;
        return false;
    }

    File.clear();
    File.seekg(CurrentPos);
    return true;
}

void SolveTurtleTask()
{
    // ifstream f("21.txt");
    // ofstream m("22.txt"); FIX_MEOW: некорректное место открытия файла для записи
    std::ifstream InputFile("21.txt");
    if (!InputFile.is_open())
    {
        std::cout << "Ошибка: Файл 21.txt не найден." << std::endl;
        return;
    }
    // int n, res;
    int N;
    int CurrentLine = 1;
    if (!SafeReadInt(InputFile, N, CurrentLine))
    {
        return;
    }

    if (N <= 1 || N >= 80)
    {
        std::cout << "Ошибка: Параметр N должен быть в диапазоне (1, 80)." << std::endl;
        return;
    }

    // Очистка буфера после чтения N для работы getline
    std::string Skip;
    std::getline(InputFile, Skip);

    // vector <vector <int>> matr(N, vector <int>(N));
    std::vector<std::vector<int>> Board(N, std::vector<int>(N));
    for (int Row = 0; Row < N; Row++)
    {
        CurrentLine++;
        if (!HasEnoughNumberInLine(InputFile, N, CurrentLine))
        {
            return;
        }

        /*for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                InputFile >> Board[i][j];
            }
        }
        */

        for (int Col = 0; Col < N; Col++)
        {
            int Value;
            if (!SafeReadInt(InputFile, Value, CurrentLine))
            {
                return;
            }
            if (Value < 0 || Value > 100)
            {
                std::cout << "Ошибка: Число " << Value << " в строке " << CurrentLine << " вне диапазона [0, 100]." << std::endl;
                return;
            }
            Board[Row][Col] = Value;
        }
        std::getline(InputFile, Skip);
    }
    InputFile.close();

    std::vector<std::vector<int>> ResultBoard(N, std::vector<int>(N, 0));

    // Движение: из правого верхнего (0, N-1) в левый нижний (N-1, 0)
    // Доступные шаги: Влево (Col--) или Вниз (Row++)
    for (int Row = 0; Row < N; Row++)
    {
        for (int Col = N - 1; Col >= 0; Col--)
        {
            if (Row == 0 && Col == N - 1)
            {
                // Старт
                ResultBoard[Row][Col] = Board[Row][Col];
            }
            else if (Row == 0)
            {
                // Верхняя строка: можно прийти только справа
                ResultBoard[Row][Col] = ResultBoard[Row][Col + 1] + Board[Row][Col];
            }
            else if (Col == N - 1)
            {
                // Правый столбец: можно прийти только сверху
                ResultBoard[Row][Col] = ResultBoard[Row - 1][Col] + Board[Row][Col];
            }
            else
            {
                // Обычная клетка: выбираем максимум между «прийти сверху» или «прийти справа»
                ResultBoard[Row][Col] = std::max(ResultBoard[Row - 1][Col], ResultBoard[Row][Col + 1]) + Board[Row][Col];
            }
        }
    }

    int FinalSum = ResultBoard[N - 1][0];

    std::ofstream OutputFile("22.txt");
    if (OutputFile.is_open())
    {
        OutputFile << FinalSum;
        OutputFile.close();
        std::cout << "Максимальная сумма: " << FinalSum << std::endl;
    }
    else
    {
        std::cout << "Ошибка: Не удалось создать файл 22.txt" << std::endl;
    }
}