#pragma once
#include <iostream>
#include <cmath>

class Vector3 {
public:
    float x;
    float y;
    float z;

    Vector3();
    Vector3(float x, float y, float z);

     /// Function Declarations
    /* Operation Functions */
    Vector3 operator + (const Vector3& v);
    Vector3 operator - (const Vector3& v);
    Vector3 operator / (const Vector3& v);
    Vector3 operator * (const Vector3& v);
    Vector3 operator * (float s);

    /* Dot and Cross Product */
    void Dot(Vector3& v);
    void Cross(Vector3& v);

    /* Magnitude and Normalisation */
    float Magnitude();
    void Normalisation();
};