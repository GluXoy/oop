#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../multmatrix/multmatrix.h"

SCENARIO("Multiplication of matrices with int elems")
{
    double mx1[MATRIX_SIZE][MATRIX_SIZE] = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
    double mx2[MATRIX_SIZE][MATRIX_SIZE] = { {9, 8, 7}, {6, 5, 4}, {3, 2, 1} };
    double result[MATRIX_SIZE][MATRIX_SIZE];

    MultiplyMatrices(mx1, mx2, result);

    SECTION("Check multiplication result")
    {
        REQUIRE(result[0][0] == Approx(30));
        REQUIRE(result[0][1] == Approx(24));
        REQUIRE(result[0][2] == Approx(18));
        REQUIRE(result[1][0] == Approx(84));
        REQUIRE(result[1][1] == Approx(69));
        REQUIRE(result[1][2] == Approx(54));
        REQUIRE(result[2][0] == Approx(138));
        REQUIRE(result[2][1] == Approx(114));
        REQUIRE(result[2][2] == Approx(90));
    }
}

SCENARIO("Multiplication of matrices with float(1) elems")
{
    double mx1[MATRIX_SIZE][MATRIX_SIZE] = { {1.1, 2.2, 3.3}, {4.4, 5.5, 6.6}, {7.7, 8.8, 9.9} };
    double mx2[MATRIX_SIZE][MATRIX_SIZE] = { {9.9, 8.8, 7.7}, {6.6, 5.5, 4.4}, {3.3, 2.2, 1.1} };
    double result[MATRIX_SIZE][MATRIX_SIZE];

    MultiplyMatrices(mx1, mx2, result);

    SECTION("Check multiplication result")
    {
        REQUIRE(result[0][0] == Approx(36.3));
        REQUIRE(result[0][1] == Approx(29.04));
        REQUIRE(result[0][2] == Approx(21.78));
        REQUIRE(result[1][0] == Approx(101.64));
        REQUIRE(result[1][1] == Approx(83.49));
        REQUIRE(result[1][2] == Approx(65.34));
        REQUIRE(result[2][0] == Approx(166.98));
        REQUIRE(result[2][1] == Approx(137.94));
        REQUIRE(result[2][2] == Approx(108.9));
    }
}

SCENARIO("Multiplication of matrices with float(3) elems")
{
    double mx1[MATRIX_SIZE][MATRIX_SIZE] = { {1.111, 2.222, 3.333}, {4.444, 5.555, 6.666}, {7.777, 8.888, 9.999} };
    double mx2[MATRIX_SIZE][MATRIX_SIZE] = { {9.999, 8.888, 7.777}, {6.666, 5.555, 4.444}, {3.333, 2.222, 1.111} };
    double result[MATRIX_SIZE][MATRIX_SIZE];

    MultiplyMatrices(mx1, mx2, result);

    SECTION("Check multiplication result")
    {
        REQUIRE(result[0][0] == Approx(37.029).epsilon(0.001));
        REQUIRE(result[0][1] == Approx(29.623).epsilon(0.001));
        REQUIRE(result[0][2] == Approx(22.217).epsilon(0.001));
        REQUIRE(result[1][0] == Approx(103.682).epsilon(0.001));
        REQUIRE(result[1][1] == Approx(85.168).epsilon(0.001));
        REQUIRE(result[1][2] == Approx(66.653).epsilon(0.001));
        REQUIRE(result[2][0] == Approx(170.336).epsilon(0.001));
        REQUIRE(result[2][1] == Approx(140.712).epsilon(0.001));
        REQUIRE(result[2][2] == Approx(111.088).epsilon(0.001));
    }
}
