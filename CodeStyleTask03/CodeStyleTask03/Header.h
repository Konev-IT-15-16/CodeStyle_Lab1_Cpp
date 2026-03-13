#pragma once

#include <string>

// –ешение задачи о поиске количества K-ичных чисел с 4 и более нул€ми подр€д
void SolveKBaseTask();

// ѕроверка, €вл€етс€ ли строка числом
bool IsNumber(const std::string& Str);

// Ѕезопасное чтение целого числа из консоли с проверкой на корректность
bool SafeReadIntFromConsole(int& OutValue);