#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

const int MATRIX_SIZE = 3;

void multiplyMatrices(float mx1[MATRIX_SIZE][MATRIX_SIZE],
                        float mx2[MATRIX_SIZE][MATRIX_SIZE],
                        float result[MATRIX_SIZE][MATRIX_SIZE])
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

void printMatrix(float mx[MATRIX_SIZE][MATRIX_SIZE])
{
    for (int i = 0; i < MATRIX_SIZE; ++i)
    {
        for (int j = 0; j < MATRIX_SIZE; ++j)
        {
            cout << fixed << setprecision(3) << mx[i][j] << " ";
        }
        cout << endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Usage: " << argv[0] << " <matrix file1> <matrix file2>" << endl;
        return 1;
    }

    ifstream file1(argv[1]);
    ifstream file2(argv[2]);

    if (!file1 || !file2) {
        cout << "Error: Unable to open input files." << endl;
        return 1;
    }

    float mx1[MATRIX_SIZE][MATRIX_SIZE];
    float mx2[MATRIX_SIZE][MATRIX_SIZE];

    for (int i = 0; i < MATRIX_SIZE; ++i)
    {
        for (int j = 0; j < MATRIX_SIZE; ++j) 
        {
            if (!(file1 >> mx1[i][j]) || !(file2 >> mx2[i][j]))
            {
                cout << "Error: Invalid input format." << endl;
                return 1;
            }
        }
    }

    file1.close();
    file2.close();

    float result[MATRIX_SIZE][MATRIX_SIZE];

    multiplyMatrices(mx1, mx2, result);
    printMatrix(result);

    return 0;
}