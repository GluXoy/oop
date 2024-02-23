#pragma once

std::string IntToString(int num, int radix, const int RADIX_MAX);
int StringToInt(const std::string& str, int radix);
void ParseArguments(char* argv[], int& sourceNotation, int& destinationNotation, std::string& value,
    const int RADIX_MIN, const int RADIX_MAX);
std::string ConvertNotation(int& sourceNotation, int& destinationNotation, std::string& value,
    const int RADIX_MAX);