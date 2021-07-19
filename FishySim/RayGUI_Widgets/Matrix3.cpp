#include "Matrix3.h"

Matrix3::Matrix3() {
    m1 = 1; m2 = 0; m3 = 0;  
    m4 = 0; m5 = 1; m6 = 0;  
    m7 = 0; m8 = 0; m9 = 1;
}

Matrix3::Matrix3(float m1, float m2, float m3, float m4, float m5, float m6, float m7, float m8, float m9) {
    this->m1 = m1; this->m2 = m2; this->m3 = m3;   
    this->m4 = m4; this->m5 = m5; this->m6 = m6;   
    this->m7 = m7; this->m8 = m8; this->m9 = m9;
}

  /// OPERATOR OVERRIDES
#pragma region [ Operator Overrides ]
/* Overload Matrix4 addition */
Matrix3 Matrix3::operator+(const Matrix3& v) {
    Matrix3 temp;
    temp.m1 = m1 + v.m1; temp.m2 = m2 + v.m2; temp.m3 = m3 + v.m3;    
    temp.m4 = m4 + v.m4; temp.m5 = m5 + v.m5; temp.m6 = m6 + v.m6;
    temp.m7 = m7 + v.m7; temp.m8 = m8 + v.m8; temp.m9 = m9 + v.m9;
    return temp;
}

/* Overload Matrix4 subtraction */
Matrix3 Matrix3::operator-(const Matrix3& v) {
    Matrix3 temp;
    temp.m1 = m1 - v.m1; temp.m2 = m2 - v.m2; temp.m3 = m3 - v.m3;
    temp.m4 = m4 - v.m4; temp.m5 = m5 - v.m5; temp.m6 = m6 - v.m6;
    temp.m7 = m7 - v.m7; temp.m8 = m8 - v.m8; temp.m9 = m9 - v.m9;
    return temp;
}

/* Overload Matrix4 division */
Matrix3 Matrix3::operator/(const Matrix3& v) {
    Matrix3 temp;
    temp.m1 = m1 / v.m1; temp.m2 = m2 / v.m2; temp.m3 = m3 / v.m3;
    temp.m4 = m4 / v.m4; temp.m5 = m5 / v.m5; temp.m6 = m6 / v.m6;
    temp.m7 = m7 / v.m7; temp.m8 = m8 / v.m8; temp.m9 = m9 / v.m9;
    return temp;
}

/* Overload Matrix4 multiplication */
Matrix3 Matrix3::operator*(const Matrix3& v) {
    Matrix3 temp;
    temp.m1 = (m1 * v.m1) + (m2 * v.m4) + (m3 * v.m7); temp.m2 = (m1 * v.m2) + (m2 * v.m5) + (m3 * v.m8); temp.m3 = (m1 * v.m3) + (m2 * v.m6) + (m3 * v.m9);
    temp.m4 = (m4 * v.m1) + (m5 * v.m4) + (m6 * v.m7); temp.m5 = (m4 * v.m2) + (m5 * v.m5) + (m6 * v.m8); temp.m6 = (m4 * v.m3) + (m5 * v.m6) + (m6 * v.m9);
    temp.m7 = (m7 * v.m1) + (m8 * v.m4) + (m9 * v.m7); temp.m8 = (m7 * v.m2) + (m8 * v.m5) + (m9 * v.m8); temp.m9 = (m7 * v.m3) + (m8 * v.m6) + (m9 * v.m9);
    return temp;
}

/* Overload Matrix4 multiplication with Scalar */
Matrix3 Matrix3::operator*(float s) {
    Matrix3 temp;
    temp.m1 = m1 * s; temp.m2 = m2 * s; temp.m3 = m3 * s;
    temp.m4 = m4 * s; temp.m5 = m5 * s; temp.m6 = m6 * s;
    temp.m7 = m7 * s; temp.m8 = m8 * s; temp.m9 = m9 * s;
    return temp;
}
#pragma endregion

#pragma region [ Set Functions ]

void Matrix3::SetM3(float m1, float m2, float m3, float m4, float m5, float m6, float m7, float m8, float m9) {
    this->m1 = m1; this->m2 = m2; this->m3 = m3;
    this->m4 = m4; this->m5 = m5; this->m6 = m6;
    this->m7 = m7; this->m8 = m8; this->m9 = m9;
}

void Matrix3::SetM3(Matrix3 M3) {
    this->m1 = M3.m1; this->m2 = M3.m2; this->m3 = M3.m3;
    this->m4 = M3.m4; this->m5 = M3.m5; this->m6 = M3.m6;
    this->m7 = M3.m7; this->m8 = M3.m8; this->m9 = M3.m9;
}
#pragma endregion

  /// MATRIX ROTATION FUNCTIONS
#pragma region [ Rotation Functions ]
/* x-Axis Set Rotation */
void Matrix3::SetRotateX(double radians) {
    SetM3(1, 0, 0, 0, (float)cos(radians), (float)sin(radians), 0, (float)-sin(radians), (float)cos(radians));
}

/* x-Axis Rotation */
void Matrix3::RotateX(double radians) {
    Matrix3 matrix;
    matrix.SetRotateX(radians);
    SetM3(*this * matrix);
}

/* y-Axis Set Rotation */
void Matrix3::SetRotateY(double radians) {
    SetM3((float)cos(radians), 0, (float)-sin(radians), 0, 1, 0, (float)sin(radians), 0, (float)cos(radians));
}

/* y-Axis Rotation */
void Matrix3::RotateY(double radians) {
    Matrix3 matrix;
    matrix.SetRotateY(radians);
    SetM3(*this * matrix);
}

/* z-Axis Set Rotation */
void Matrix3::SetRotateZ(double radians) {
    SetM3((float)cos(radians), (float)sin(radians), 0, (float)-sin(radians), (float)cos(radians), 0, 0, 0, 1);
}

/* z-Axis Rotation */
void Matrix3::RotateZ(double radians) {
    Matrix3 matrix;
    matrix.SetRotateZ(radians);
    SetM3(*this * matrix);
}
#pragma endregion

 /// TRANSLATION FUNCTIONS
#pragma region [ Translation ]
/* Translation */
void Matrix3::SetTranslate(float x, float y) {
    m1 = 1; m2 = 0; m3 = 0;
    m4 = 0; m5 = 1; m6 = 0;
    m7 = x; m8 = y; m9 = 1;
}

void Matrix3::Translate(float x, float y) {
    Matrix3 t = Matrix3(1, 0, 0, 0, 1, 0, 0, 0, 1);
    t.SetTranslate(x, y);
    SetM3(t * *this);
}
#pragma endregion
