#pragma once
#include <iostream>
#include <cmath>

class Matrix3 {
public:
    float m1, m2, m3, m4, m5, m6, m7, m8, m9;

    Matrix3();
    Matrix3(float m1, float m2, float m3, float m4, float m5, float m6, float m7, float m8, float m9);

     /// Function Declarations
    /* Operation Functions */
    Matrix3 operator + (const Matrix3& v);
    Matrix3 operator - (const Matrix3& v);
    Matrix3 operator / (const Matrix3& v);
    Matrix3 operator * (const Matrix3& v);
    Matrix3 operator * (float s);

    /* Set Matrix3 Functions*/
    void SetM3(float m1, float m2, float m3, float m4, float m5, float m6, float m7, float m8, float m9);
    void SetM3(Matrix3 M3);

    /* Matrix3 Rotation Functions */
    void SetRotateX(double radians);
    void RotateX(double radians);
    void SetRotateY(double radians);
    void RotateY(double radians);
    void SetRotateZ(double radians);
    void RotateZ(double radians);

    /* Matrix3 Translation */
    void SetTranslate(float x, float y);
    void Translate(float x, float y);
};

