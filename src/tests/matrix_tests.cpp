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
}