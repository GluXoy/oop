#include <iostream>
#include <fstream>
#include <iomanip>
#include "multmatrix.h"

/*ля матриц std::array*/

void MultiplyMatrices(double mx1[MATRIX_SIZE][MATRIX_SIZE],
    double mx2[MATRIX_SIZE][MATRIX_SIZE],
    double result[MATRIX_SIZE][MATRIX_SIZE])
{
    for (int i = 0; i < MATRIX_SIZE; ++i)
    {
        for (int j = 0; j < MATRIX_SIZE; ++j)
        {
            result[i][j] = 0;
            for (int k = 0; k < MATRIX_SIZE; ++k)
            {
                result[i][j] += mx1[i][k] * mx2[k][j];
            }
        }
    }
}

void PrintMatrix(double mx[MATRIX_SIZE][MATRIX_SIZE])
{
    for (int i = 0; i < MATRIX_SIZE; ++i)
    {
        for (int j = 0; j < MATRIX_SIZE; ++j)
        {
            std::cout << std::fixed << std::setprecision(3) << mx[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void ParseCommandLine(int argc, char* argv[], std::string& matrixFile1, std::string& matrixFile2)
{
    if (argc != 3)
    {
        throw std::invalid_argument("Usage: " + std::string(argv[0]) + " <matrix file1> <matrix file2>");
    }
    matrixFile1 = argv[1];
    matrixFile2 = argv[2];
}


void ReadMatrixFromFile(const std::string& filename, double matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    std::ifstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("Unable to open file: " + filename);
    }

    for (int i = 0; i < MATRIX_SIZE; ++i)
    {
        for (int j = 0; j < MATRIX_SIZE; ++j)
        {
            if (!(file >> matrix[i][j]))
            {
                throw std::runtime_error("Reading matrix from file: " + filename);
            }
        }
    }

    //необязательно вызывать
    file.close();
}

void MultiplyAndPrintMatrices(const std::string& matrixFile1, const std::string& matrixFile2)
{
    double mx1[MATRIX_SIZE][MATRIX_SIZE];
    double mx2[MATRIX_SIZE][MATRIX_SIZE];

    ReadMatrixFromFile(matrixFile1, mx1);
    ReadMatrixFromFile(matrixFile2, mx2);

    double result[MATRIX_SIZE][MATRIX_SIZE];
    MultiplyMatrices(mx1, mx2, result);
    PrintMatrix(result);
}