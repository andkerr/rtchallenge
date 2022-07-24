#ifndef MATRIX_H
#define MATRIX_H

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
                if (m[i][j] != rhs.m[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }

    bool operator!=(const Matrix4x4 &rhs) const {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                if (m[i][j] != rhs.m[i][j]) {
                    return true;
                }
            }
        }
        return false;
    }

    // Matrix4x4 Public Data

    double m[4][4];
};

#endif // MATRIX_H