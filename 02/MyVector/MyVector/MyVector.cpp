#include <vector>
#include <algorithm>
#include <numeric>
#include <iostream>

void ReadNumbersFromStream(std::istream& stream, std::vector<float>& arr)
{
    float num;
    while (stream >> num)
    {
        arr.push_back(num);
    }
}

void PrintArray(const std::vector<float>& arr)
{
    for (const auto& num : arr)
    {
        std::cout << num << " ";
    }
    std::cout << '\n';
}

void UpdateArray(std::vector<float>& arr)
{
    std::vector<float> destination(3);

    std::partial_sort_copy(arr.begin(), arr.end(), destination.begin(), destination.end());
    float minSum = std::accumulate(destination.begin(), destination.end(), 0.0f);

    for (auto& num : arr)
    {
        num += minSum;
    }
}

int main()
{
    std::vector<float> arr;
    try
    {
        ReadNumbersFromStream(std::cin, arr);
        UpdateArray(arr);
        std::sort(arr.begin(), arr.end());
        PrintArray(arr);
    }
    catch (const std::exception&)
    {
        return 1;
    }
    
    return 0;
}
