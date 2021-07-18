#pragma once
#include <iostream>
#include <cmath>

using namespace std;

class Vector2 {
public:
    float x;
    float y;

    Vector2();
    Vector2(float x, float y);

    /// Function Declarations
   /* Operation Functions */
    Vector2 operator + (const Vector2& v);
    Vector2 operator - (const Vector2& v);
    Vector2 operator / (const Vector2& v);
    Vector2 operator * (const Vector2& v);
    Vector2 operator * (float s);

    /* Dot Function */
    void Dot(Vector2& v);

    /* Magnitude and Normalisation */
    float Magnitude();
    void Normalisation();
};