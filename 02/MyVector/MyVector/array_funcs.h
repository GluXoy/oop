#pragma once
#include <vector>
#include <iostream>

void ReadNumbersFromStream(std::istream& stream, std::vector<double>& arr);

void PrintArray(const std::vector<double>& arr);

void UpdateArray(std::vector<double>& arr);
