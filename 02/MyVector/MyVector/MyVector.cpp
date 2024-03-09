#include <vector>
#include <algorithm>
#include <numeric>
#include <iostream>
#include "array_funcs.h"

int main()
{
    std::vector<double> arr;
    try
    {
        ReadNumbersFromStream(std::cin, arr);
        UpdateArray(arr);
        std::sort(arr.begin(), arr.end());
        PrintArray(arr);
    }
    catch (const std::exception& ex)
    {
        std::cout << ex.what() << '\n';
        return 1;
    }
    
    return 0;
}
