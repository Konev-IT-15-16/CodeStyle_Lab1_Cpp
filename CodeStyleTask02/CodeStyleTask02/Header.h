#pragma once

#include <string>
#include <vector>
#include <fstream>

// Решение задачи с Черепашкой
void SolveTurtleTask();

// Проверка, является ли строка корректным числом
bool IsNumber(const std::string& Str);

// Безопасное чтение целого числа из потока с проверкой ошибок
bool SafeReadInt(std::ifstream& File, int& Value, int LineNum);

// Проверка соответствия кол-ва чисел в строке
bool HasEnoughNumberInLine(std::ifstream& File, int RequiredCount, int LineNum);