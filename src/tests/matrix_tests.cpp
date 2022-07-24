#include "matrix.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Matrix Tests") {
    SECTION("Default Matrix4x4 initializes the identity matrix") {
        Matrix4x4 mat;

        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                if (i == j) {
                    REQUIRE(mat.m[i][j] == 1);
                }
                else {
                    REQUIRE(mat.m[i][j] == 0);
                }
            }
        }
    }

    SECTION("Matrix4x4 supports random access in the style of a 2D array") {
        Matrix4x4 mat(1, 2, 3, 4,
                      5.5, 6.5, 7.5, 8.5,
                      9, 10, 11, 12,
                      13.5, 14.5, 15.5, 16.5);
        
        REQUIRE(mat.m[0][0] == 1);
        REQUIRE(mat.m[0][3] == 4);
        REQUIRE(mat.m[1][0] == 5.5);
        REQUIRE(mat.m[1][2] == 7.5);
        REQUIRE(mat.m[2][2] == 11);
        REQUIRE(mat.m[3][0] == 13.5);
        REQUIRE(mat.m[3][2] == 15.5); 
    }

    SECTION("Matrices that have the same elements compare equal") {
        Matrix4x4 mat1(1, 2, 3, 4,
                       5, 6, 7, 8,
                       9, 8, 7, 6,
                       5, 4, 3, 2);
        Matrix4x4 mat2(1, 2, 3, 4,
                       5, 6, 7, 8,
                       9, 8, 7, 6,
                       5, 4, 3, 2);

        REQUIRE(mat1 == mat2);
        REQUIRE(!(mat1 != mat2));
    }

    SECTION("Matrices with any number (greater than 0) of differing elements compare unequal") {
        Matrix4x4 mat1(1, 2, 3, 4,
                       5, 6, 7, 8,
                       9, 8, 7, 6,
                       5, 4, 3, 2);
        Matrix4x4 mat2(1, 2, 3, 4,
                       5, 6, 7, 8,
                       9, 8, 7, 6,
                       5, 4, 3, 0);

        REQUIRE(mat1 != mat2);
        REQUIRE(!(mat1 == mat2));
    }

    SECTION("Matrices support the matrix product") {
        Matrix4x4 mat1(1, 2, 3, 4,
                       5, 6, 7, 8,
                       9, 8, 7, 6,
                       5, 4, 3, 2);
        Matrix4x4 mat2(-2, 1, 2, 3,
                       3, 2, 1, -1,
                       4, 3, 6, 5,
                       1, 2, 7, 8);

        Matrix4x4 result = mat1.mul(mat2);
        Matrix4x4 expected(20, 22, 50, 48,
                           44, 54, 114, 108,
                           40, 58, 110, 102,
                           16, 26, 46, 42);
        REQUIRE(result == expected);
    }

    SECTION("Matrices can be used to mutlipy Tuples") {
        Matrix4x4 mat(1, 2, 3, 4,
                      2, 4, 4, 2,
                      8, 6, 4, 1,
                      0, 0, 0, 1);
        Tuple t(1, 2, 3, 1);

        REQUIRE(mat.mul(t) == Tuple(18, 24, 33, 1));
    }

    SECTION("Multiplying a Matrix or Tuple by the identity matrix returns the original Matrix or Tuple") {
        Matrix4x4 mat(0, 1, 2, 4,
                      1, 2, 4, 8,
                      2, 4, 8, 16,
                      4, 8, 16, 32);
        Matrix4x4 identity;

        REQUIRE(mat.mul(identity) == mat);

        Tuple t(1, 2, 3, 4);
        REQUIRE(identity.mul(t) == t);
    }

    SECTION("The matrix transpose reflects elements across the main diagonal") {
        Matrix4x4 mat(0, 9, 3, 0,
                      9, 8, 0, 8,
                      1, 8, 5, 3,
                      0, 0, 5, 8);
        Matrix4x4 expected(0, 9, 1, 0,
                           9, 8, 8, 0,
                           3, 0, 5, 5,
                           0, 8, 3, 8);

        REQUIRE(mat.transpose() == expected);
    }

    SECTION("Transposing the identity matrix returns the identity matrix") {
        Matrix4x4 identity;
        REQUIRE(identity.transpose() == identity);
    }

    SECTION("Matrix inversion") {
        Matrix4x4 mat(-5, 2, 6, -8,
                      1, -5, 1, 8,
                      7, 7, -6, -7,
                      1, -3, 7, 4);
        Matrix4x4 expected(0.21805, 0.45113, 0.24060, -0.04511,
                           -0.80827, -1.45677, -0.44361, 0.52068,
                           -0.07895, -0.22368, -0.05263, 0.19737,
                           -0.52256, -0.81391, -0.30075, 0.30639);

        REQUIRE(mat.inverse() == expected);

        mat = Matrix4x4(8, -5, 9, 2,
                        7, 5, 6, 1,
                        -6, 0, 9, 6,
                        -3, 0, -9, -4);
        expected = Matrix4x4(-0.15385, -0.15385, -0.28205, -0.53846,
                             -0.07692,  0.12308,  0.02564,  0.03077,
                             0.35897, 0.35897,  0.43590,  0.92308,
                             -0.69231, -0.69231, -0.76923, -1.92308);
    
        REQUIRE(mat.inverse() == expected);

        mat = Matrix4x4(9, 3, 0, 9,
                        -5, -2, -6, -3,
                        -4, 9, 6, 4,
                        -7, 6, 6, 2);
        expected = Matrix4x4(-0.04074, -0.07778,  0.14444, -0.22222,
                             -0.07778,  0.03333,  0.36667, -0.33333,
                             -0.02901, -0.14630, -0.10926,  0.12963,
                             0.17778, 0.06667, -0.26667, 0.33333);
                            
        REQUIRE(mat.inverse() == expected);
    }

    SECTION("Multiplying a matrix by its inverse returns the identity") {
        Matrix4x4 mat(9, 3, 0, 9,
                      -5, -2, -6, -3,
                      -4, 9, 6, 4,
                      -7, 6, 6, 2);
        Matrix4x4 identity;
                            
        REQUIRE(mat.mul(mat.inverse()) == identity);
    }
}