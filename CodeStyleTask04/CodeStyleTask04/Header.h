#pragma once

#include <string>

// ¬ычисл€ет значение логического выражени€.
bool ParseLogicalExpression(const std::string& ExpressionString, int& PositionIndex);

// –екурсивно провер€ет наличие пробелов в строке.
bool HasSpaces(const std::string& ExpressionString, int PositionIndex);