#ifndef MATRIX_H
#define MATRIX_H

#include "double.h"
#include "geometry.h"

#include <iostream>

struct Matrix4x4 {
    Matrix4x4() {
        m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1.0;
        m[0][1] = m[0][2] = m[0][3] =
        m[1][0] = m[1][2] = m[1][3] =
        m[2][0] = m[2][1] = m[2][3] =
        m[3][0] = m[3][1] = m[3][2] = 0.0;
    }

    Matrix4x4(double m_in[4][4]);
    Matrix4x4(double m00, double m01, double m02, double m03,
              double m10, double m11, double m12, double m13,
              double m20, double m21, double m22, double m23,
              double m30, double m31, double m32, double m33);

    bool operator==(const Matrix4x4 &rhs) const {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                if (!doubleEqual(m[i][j], rhs.m[i][j])) {
                    return false;
                }
            }
        }
        return true;
    }

    bool operator!=(const Matrix4x4 &rhs) const {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                if (!doubleEqual(m[i][j], rhs.m[i][j])) {
                    return true;
                }
            }
        }
        return false;
    }

    Matrix4x4 mul(const Matrix4x4 &rhs) const {
        Matrix4x4 res;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                res.m[i][j] = (m[i][0] * rhs.m[0][j] +
                               m[i][1] * rhs.m[1][j] +
                               m[i][2] * rhs.m[2][j] +
                               m[i][3] * rhs.m[3][j]);
            }
        }

        // This looks wrong, I might need an element-wise copy
        // somewhere around here...
        return res;
    }

    Tuple mul(const Tuple& rhs) const {
        Tuple res;
        res.x = (m[0][0] * rhs.x +
                 m[0][1] * rhs.y +
                 m[0][2] * rhs.z +
                 m[0][3] * rhs.w);

        res.y = (m[1][0] * rhs.x +
                 m[1][1] * rhs.y +
                 m[1][2] * rhs.z +
                 m[1][3] * rhs.w);

        res.z = (m[2][0] * rhs.x +
                 m[2][1] * rhs.y +
                 m[2][2] * rhs.z +
                 m[2][3] * rhs.w);

        res.w = (m[3][0] * rhs.x +
                 m[3][1] * rhs.y +
                 m[3][2] * rhs.z +
                 m[3][3] * rhs.w);
                
        return res;
    }

    Matrix4x4 transpose() {
        return Matrix4x4(m[0][0], m[1][0], m[2][0], m[3][0],
                         m[0][1], m[1][1], m[2][1], m[3][1],
                         m[0][2], m[1][2], m[2][2], m[3][2],
                         m[0][3], m[1][3], m[2][3], m[3][3]);
    }

    Matrix4x4 inverse() const;

    // Matrix4x4 Public Data

    double m[4][4];
};

std::ostream &operator<<(std::ostream& os, const Matrix4x4& mat);

#endif // MATRIX_H