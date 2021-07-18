#include "Vector2.h"

Vector2::Vector2() {
    x = 0;
    y = 0;
}

Vector2::Vector2(float x, float y) {
    this->x = x;
    this->y = y;
}

  /// OPERATOR OVERRIDES
#pragma region [ Operator Overrides ]
/* Overload Vector2 addition */
Vector2 Vector2::operator+(const Vector2& vector) {
    Vector2 temp;
    temp.x = x + vector.x;
    temp.y = y + vector.y;
    return Vector2();
}

/* Overload Vector2 subtraction */
Vector2 Vector2::operator-(const Vector2& vector) {
    Vector2 temp;
    temp.x = x - vector.x;
    temp.y = y - vector.y;
    return Vector2();
}

/* Overload Vector2 division */
Vector2 Vector2::operator/(const Vector2& vector) {
    Vector2 temp;
    temp.x = x / vector.x;
    temp.y = y / vector.y;
    return Vector2();
}

/* Overload Vector2 multiplication */
Vector2 Vector2::operator*(const Vector2& vector) {
    Vector2 temp;
    temp.x = x * vector.x;
    temp.y = y * vector.y;
    return Vector2();
}

/* Overload Vector2 multiplication with Scalar */
Vector2 Vector2::operator*(float scalar) {
    Vector2 temp;
    temp.x = x * scalar;
    temp.y = y * scalar;
    return Vector2();
}

#pragma endregion

 /// DOT
/* Vector2 Dot */
void Vector2::Dot(Vector2& vector) {
    x = x * vector.x;
    y = y * vector.y;
}

#pragma endregion

  /// MAGNITUDE and NORMALISATION
#pragma region [ Magnitude and Normalisation ]
/* Vector2 Magnitude */
float Vector2::Magnitude() {
    return sqrt(x * x) + (y * y);
}

/* Vector3 Normalisation */
void Vector2::Normalisation() {
    float magnitude = Magnitude();

    x /= magnitude;
    y /= magnitude;
}

#pragma endregion