#include "Header.h"
#include <iostream>

// FIX_MEOW: некорректные названия переменных

// FIX_MEOW: добавлены поясняющие комментарии

/* FIX_MEOW: нарушение условия задания (наличие цикла)
while (i < s.length() && s[i] == ' ')
{
    i++;
}
*/
// Рекурсивно проверяет наличие пробелов в строке.
bool HasSpaces(const std::string& ExpressionString, int PositionIndex)
{
    if (PositionIndex >= (int)ExpressionString.length())
    {
        return false;
    }

    if (ExpressionString[PositionIndex] == ' ')
    {
        return true;
    }

    return HasSpaces(ExpressionString, PositionIndex + 1);
}

// Вычисляет значение логического выражения.
// bool F(const std::string& s, int& i) FIX_MEOW: некорректные названия функции и переменных
bool ParseLogicalExpression(const std::string& ExpressionString, int& PositionIndex)
{
    if (PositionIndex >= (int)ExpressionString.length())
    {
        return false;
    }

    // Обработка константы True
    if (ExpressionString[PositionIndex] == 'T')
    {
        PositionIndex++;
        return true;
    }

    // Обработка константы False
    if (ExpressionString[PositionIndex] == 'F')
    {
        PositionIndex++;
        return false;
    }

    // Обработка оператора And(Left, Right)
    // bool l, r;
    if (ExpressionString.substr(PositionIndex, 4) == "And(")
    {
        PositionIndex += 4;
        bool LeftValue = ParseLogicalExpression(ExpressionString, PositionIndex);

        // Безопасный пропуск разделителя (запятой)
        if (PositionIndex < (int)ExpressionString.length() && ExpressionString[PositionIndex] == ',')
        {
            PositionIndex++;
        }

        bool RightValue = ParseLogicalExpression(ExpressionString, PositionIndex);

        // Безопасный пропуск закрывающей скобки
        if (PositionIndex < (int)ExpressionString.length() && ExpressionString[PositionIndex] == ')')
        {
            PositionIndex++;
        }

        return LeftValue && RightValue;
    }

    // Обработка оператора Or(Left, Right)
    if (ExpressionString.substr(PositionIndex, 3) == "Or(")
    {
        PositionIndex += 3;
        bool LeftValue = ParseLogicalExpression(ExpressionString, PositionIndex);

        // Безопасный пропуск разделителя (запятой)
        if (PositionIndex < (int)ExpressionString.length() && ExpressionString[PositionIndex] == ',')
        {
            PositionIndex++;
        }

        bool RightValue = ParseLogicalExpression(ExpressionString, PositionIndex);

        // Безопасный пропуск закрывающей скобки
        if (PositionIndex < (int)ExpressionString.length() && ExpressionString[PositionIndex] == ')')
        {
            PositionIndex++;
        }

        return LeftValue || RightValue;
    }

    return false;
}