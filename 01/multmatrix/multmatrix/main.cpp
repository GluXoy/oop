#include <iostream>
#include <fstream>
#include <iomanip>
#include "multmatrix.h"

using namespace std;

int main(int argc, char* argv[])
{
    string matrixFile1; 
    string matrixFile2;

    try {
        ParseCommandLine(argc, argv, matrixFile1, matrixFile2);
        MultiplyAndPrintMatrices(matrixFile1, matrixFile2);
    }
    catch (const exception& ex) {
        cout << "Error: " << ex.what() << '\n';
        return 1;
    }

    return 0;
}