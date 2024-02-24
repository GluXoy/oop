#pragma once

const int MATRIX_SIZE = 3;

void MultiplyMatrices(double mx1[MATRIX_SIZE][MATRIX_SIZE],
    double mx2[MATRIX_SIZE][MATRIX_SIZE],
    double result[MATRIX_SIZE][MATRIX_SIZE]);

void PrintMatrix(double mx[MATRIX_SIZE][MATRIX_SIZE]);
void ParseCommandLine(int argc, char* argv[], std::string& matrixFile1, std::string& matrixFile2);
void ReadMatrixFromFile(const std::string& filename, double matrix[MATRIX_SIZE][MATRIX_SIZE]);
void MultiplyAndPrintMatrices(const std::string& matrixFile1, const std::string& matrixFile2);