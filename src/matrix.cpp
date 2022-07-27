#include "matrix.h"

#include <cassert>
#include <iostream>

Matrix4x4::Matrix4x4(double m_in[4][4]) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            m[i][j] = m_in[i][j];
        }
    }
}

Matrix4x4::Matrix4x4(double m00, double m01, double m02, double m03,
                     double m10, double m11, double m12, double m13,
                     double m20, double m21, double m22, double m23,
                     double m30, double m31, double m32, double m33) {
    m[0][0] = m00;
    m[0][1] = m01;
    m[0][2] = m02;
    m[0][3] = m03;
    m[1][0] = m10;
    m[1][1] = m11;
    m[1][2] = m12;
    m[1][3] = m13;
    m[2][0] = m20;
    m[2][1] = m21;
    m[2][2] = m22;
    m[2][3] = m23;
    m[3][0] = m30;
    m[3][1] = m31;
    m[3][2] = m32;
    m[3][3] = m33;
}

// Matrix Inversion from Gauss-Jordan elimination,
// from Numerical Recipes (not my own code).
Matrix4x4 Matrix4x4::inverse() const {
    int indxc[4], indxr[4];
    int ipiv[4] = {0, 0, 0, 0};
    double minv[4][4];
    memcpy(minv, m, 4 * 4 * sizeof(double));
    for (int i = 0; i < 4; i++) {
        int irow = 0, icol = 0;
        double big = 0;
        // Choose pivot
        for (int j = 0; j < 4; j++) {
            if (ipiv[j] != 1) {
                for (int k = 0; k < 4; k++) {
                    if (ipiv[k] == 0) {
                        if (std::abs(minv[j][k]) >= big) {
                            big = double(std::abs(minv[j][k]));
                            irow = j;
                            icol = k;
                        }
                    } 
                    else if (ipiv[k] > 1) {
                        assert(false); // Singular matrix
                    }
                }
            }
        }
        ++ipiv[icol];
        // Swap rows _irow_ and _icol_ for pivot
        if (irow != icol) {
            for (int k = 0; k < 4; ++k) {
                std::swap(minv[irow][k], minv[icol][k]);
            }
        }
        indxr[i] = irow;
        indxc[i] = icol;
        if (minv[icol][icol] == 0.0) {
            assert(false); // Singular matrix
        }

        // Set $m[icol][icol]$ to one by scaling row _icol_ appropriately
        double pivinv = 1.0 / minv[icol][icol];
        minv[icol][icol] = 1.0;
        for (int j = 0; j < 4; j++) {
            minv[icol][j] *= pivinv;
        }

        // Subtract this row from others to zero out their columns
        for (int j = 0; j < 4; j++) {
            if (j != icol) {
                double save = minv[j][icol];
                minv[j][icol] = 0;
                for (int k = 0; k < 4; k++) {
                    minv[j][k] -= minv[icol][k] * save;
                }
            }
        }
    }

    // Swap columns to reflect permutation
    for (int j = 3; j >= 0; j--) {
        if (indxr[j] != indxc[j]) {
            for (int k = 0; k < 4; k++)
                std::swap(minv[k][indxr[j]], minv[k][indxc[j]]);
        }
    }
    return Matrix4x4(minv);
}

std::ostream &operator<<(std::ostream& os, const Matrix4x4& mat) {
    os << "[ " << mat.m[0][0] << " " << mat.m[0][1] << " " << mat.m[0][2] << " " << mat.m[0][3] << " ]\n"
       << "[ " << mat.m[1][0] << " " << mat.m[1][1] << " " << mat.m[1][2] << " " << mat.m[1][3] << " ]\n"
       << "[ " << mat.m[2][0] << " " << mat.m[2][1] << " " << mat.m[2][2] << " " << mat.m[2][3] << " ]\n"
       << "[ " << mat.m[3][0] << " " << mat.m[3][1] << " " << mat.m[3][2] << " " << mat.m[3][3] << " ]";
    return os;
}