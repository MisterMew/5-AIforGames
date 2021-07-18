#include "Vector3.h"

Vector3::Vector3() {
    x = 0;
    y = 0;
    z = 0;
}

Vector3::Vector3(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

  /// OPERATOR OVERRIDES
#pragma region [ Operator Overrides ]
/* Overload Vector3 addition */
Vector3 Vector3::operator+(const Vector3& vector){
    Vector3 temp;
    temp.x = x + vector.x;
    temp.y = y + vector.y;
    temp.z = z + vector.z;
    return Vector3();
}

/* Overload Vector3 subtraction */
Vector3 Vector3::operator-(const Vector3& vector) {
    Vector3 temp;
    temp.x = x - vector.x;
    temp.y = y - vector.y;
    temp.z = z - vector.z;
    return Vector3();
}

/* Overload Vector3 division */
Vector3 Vector3::operator/(const Vector3& vector) {
    Vector3 temp;
    temp.x = x / vector.x;
    temp.y = y / vector.y;
    temp.z = z / vector.z;
    return Vector3();
}

/* Overload Vector3 multiplication */
Vector3 Vector3::operator*(const Vector3& vector) {
    Vector3 temp;
    temp.x = x * vector.x;
    temp.y = y * vector.y;
    temp.z = z * vector.z;
    return Vector3();
}

/* Overload Vector3 multiplication with Scalar */
Vector3 Vector3::operator*(float scalar) {
    Vector3 temp;
    temp.x = x * scalar;
    temp.y = y * scalar;
    temp.z = z * scalar;
    return Vector3();
}

#pragma endregion

  /// DOT and CROSS PRODUCT
#pragma region [ Dot and Cross ]
/* Vector3 Dot */
void Vector3::Dot(Vector3& vector) {
    x = x * vector.x;
    y = y * vector.y;
    z = z * vector.z;
}

/* Vector3 Cross Product */
void Vector3::Cross(Vector3& vector) {
    x = (y * vector.z) - (z * vector.y);
    y = (z * vector.x) - (x * vector.z);
    z = (x * vector.y) - (y * vector.x);
}

#pragma endregion

  /// MAGNITUDE and NORMALISATION
#pragma region [ Magnitude and Normalisation ]
/* Vector3 Magnitude */
float Vector3::Magnitude() {
    return sqrt(x * x) + (y * y) + (z * z);
}

/* Vector3 Normalisation */
void Vector3::Normalisation() {
    float magnitude = Magnitude();

    x /= magnitude;
    y /= magnitude;
    z /= magnitude;
}

#pragma endregion