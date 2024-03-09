#include <vector>
#include <algorithm>
#include <numeric>
#include <iostream>

void ReadNumbersFromStream(std::istream& stream, std::vector<double>& arr)
{
    double num;
    std::cout << "Enter numbers:\n";
    while (stream >> num)
    {
        arr.push_back(num);
    }
}

void PrintArray(const std::vector<double>& arr)
{
    for (const auto& num : arr)
    {
        std::cout << num << " ";
    }
    std::cout << '\n';
}

void UpdateArray(std::vector<double>& arr)
{
    std::vector<double> destination(3);

    std::partial_sort_copy(arr.begin(), arr.end(), destination.begin(), destination.end());
    double minSum = std::accumulate(destination.begin(), destination.end(), 0.0);

    for (auto& num : arr)
    {
        num += minSum;
    }
}